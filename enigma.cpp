#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

//How it works:
//User select a reflector and 3 rotors, the user writes a message and that message get encrypted changing the letters and eliminating the spaces
//using symbols will make it crash
//we have an alphabet called abc where the index represents its position in the alphabet
//then we have reflectors and rotors which instead of letters it has index positions as value, so in that way the rotor index 0 gives a value that signal the machine that instead of "A" it has to use the letter in the index position of abc pointed by the rotor value
//for example rotorI has in index 0 the value 11, thats means that when user writes "A"(index 0 in abc), the machine will use the value 11 and search in abc the letter in the index 11 and print that letter instead of "A" (in this case the letter "L" will replace "A" because is the letter in the index 11 of abc)
//the difference within the rotor and reflector is that the rotor spins one position each time the user writes a letter, the reflector stay in the same position allowing with this the ability to decrypt the message using the same rotor and reflector configuration
//actual enigma machine uses wires to further increase the encryption level, but doing that in an console will result in a very uncomfortable UX so i prefer avoiding it.
class enigma{
    private:
        const char abc[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
        const int rotorI[26]={11,0,12,1,19,7,2,17,13,3,6,22,18,14,4,23,25,5,9,16,24,8,21,15,10,20};
        const int* pRotorI= rotorI;
        const int rotorII[26]={8,13,5,4,14,23,12,17,9,0,18,11,1,3,2,24,16,6,15,22,10,20,25,21,7,19};
        const int* pRotorII= rotorII;
        const int rotorIII[26]={10,0,8,1,5,15,14,17,12,25,7,6,11,21,2,16,13,20,3,18,24,9,23,19,22,4};
        const int* pRotorIII= rotorIII;
        const int rotorIV[26]={2,19,4,3,20,14,17,10,23,12,22,25,9,1,8,15,6,11,0,16,13,24,5,21,7,18};
        const int* pRotorIV= rotorIV;
        const int rotorV[26]={14,0,20,23,1,5,24,22,17,10,8,7,15,19,11,9,21,12,25,4,16,2,18,13,3,6};
        const int* pRotorV= rotorV;
        const int rotorVI[26]={3,24,14,2,17,25,19,4,23,8,20,6,11,22,15,16,10,0,12,1,7,13,21,18,9,5};
        const int* pRotorVI= rotorVI;
        const int rotorVII[26]={2,18,5,10,15,11,8,20,14,4,7,24,22,21,6,17,13,3,19,25,1,12,16,9,0,23};
        const int* pRotorVII= rotorVII;
        const int rotorVIII[26]={11,22,0,20,2,10,8,23,21,1,19,15,17,5,14,3,7,18,12,9,25,4,24,13,6,16};
        const int* pRotorVIII= rotorVIII;
        const int reflectorA[26]={4,10,8,25,0,17,13,22,2,20,1,12,11,6,21,23,18,5,16,24,9,14,7,15,19,3};
        const int* pReflectorA= reflectorA;
        const int reflectorB[26]={10,23,15,20,13,25,12,9,11,7,0,8,6,4,21,2,19,24,22,16,3,14,18,1,17,5};
        const int* pReflectorB= reflectorB;
    public:

        //Function to make user to select between encrypting or decrypting
        void menu(){
            int option=0;

            do
            {
                cout<<"Choose one of the following options:"<<endl;
                cout<<"1- Use Enigma machine"<<endl;
                cout<<"2- Exit program"<<endl;
                cout<<endl<<"Enter the number of the option desired: ";
                cin>>option;
                cout<<endl;
            } while (option != 1 && option != 2 && option!=3);

            if (option == 1){
                configureRotors(option);
            }else if(option==2){
                return;
            }else{
                cout<<"ERROR: choosen number is not valid"<<endl;
            }
        }

        //Always have to configure the reflector and rotors before encrypting or decrypting, this determine what letter will replace the one written by the user
        void configureRotors(int userOption){
            int reflector=0;
            int firstRotor=0;
            int secondRotor=0;
            int thirdRotor=0;

            int initialReflector=0;
            int initialFirstRotor=0;
            int initialSecondRotor=0;
            int initialThirdRotor=0;

            const int* pReflector=nullptr;
            const int* pFirstRotor=nullptr;
            const int* pSecondRotor=nullptr;
            const int* pThirdRotor=nullptr;
            
            while (reflector!=1 && reflector!=2){
                cout<<endl<<"Choose the reflector (1 or 2): ";
                cin>>reflector;
            }

            while (firstRotor<1 || firstRotor>7)
            {
               cout<<endl<<"Choose the first rotor (1 to 8): ";
                cin>>firstRotor;
            }
            
            while (secondRotor<1 || secondRotor>7 || secondRotor==firstRotor)
            {
                cout<<endl<<"Choose the second rotor (1 to 8, remember not to choose the same rotor as before): ";
                cin>>secondRotor;
            }
            
            while (thirdRotor<1 || thirdRotor>7 || thirdRotor==firstRotor || thirdRotor==secondRotor)
            {
                cout<<endl<<"Choose the third rotor (1 to 8, remember not to choose the same rotor as before): ";
                cin>>thirdRotor;
            }

            cout<<endl<<"Options selected: ";
            cout<<endl<<"Reflector: "<<reflector;
            cout<<endl<<"First rotor: "<<firstRotor;
            cout<<endl<<"Second rotor: "<<secondRotor;
            cout<<endl<<"Third rotor: "<<thirdRotor;
            cout<<endl;

            while (initialReflector<1 || initialReflector>26)
            {
                cout<<endl<<"Choose the reflector starting position (1 or 26): ";
                cin>>initialReflector;
            }
            --initialReflector;

            while (initialFirstRotor<1 || initialFirstRotor>26)
            {
                cout<<endl<<"Choose the first rotor starting position (1 or 26): ";
                cin>>initialFirstRotor;
            }
            --initialFirstRotor;

            while (initialSecondRotor<1 || initialSecondRotor>26)
            {
                cout<<endl<<"Choose the second rotor starting position (1 or 26): ";
                cin>>initialSecondRotor;
            }
            --initialSecondRotor;

            while (initialThirdRotor<1 || initialThirdRotor>26)
            {
                cout<<endl<<"Choose the third rotor starting position (1 or 26): ";
                cin>>initialThirdRotor; 
            }
            --initialThirdRotor;

            cout<<endl<<"Options selected: ";
            cout<<endl<<"Reflector initial position: "<<initialReflector+1;
            cout<<endl<<"First rotor initial position: "<<initialFirstRotor+1;
            cout<<endl<<"Second rotor initial position: "<<initialSecondRotor+1;
            cout<<endl<<"Third rotor initial position: "<<initialThirdRotor+1;
            cout<<endl;

            if (reflector==1)
            {
                pReflector=pReflectorA;
            }else{
                pReflector=pReflectorB;
            }

            switch (firstRotor)
            {
            case 1:
                pFirstRotor=pRotorI;
                break;
            case 2:
                pFirstRotor=pRotorII;
                break;
            case 3:
                pFirstRotor=pRotorIII;
                break;
            case 4:
                pFirstRotor=pRotorIV;
                break;
            case 5:
                pFirstRotor=pRotorV;
                break;
            case 6:
                pFirstRotor=pRotorVI;
                break;
            case 7:
                pFirstRotor=pRotorVII;
                break;
            case 8:
                pFirstRotor=pRotorVIII;
                break;
            
            default:
                break;
            }

            switch (secondRotor)
            {
            case 1:
                pSecondRotor=pRotorI;
                break;
            case 2:
                pSecondRotor=pRotorII;
                break;
            case 3:
                pSecondRotor=pRotorIII;
                break;
            case 4:
                pSecondRotor=pRotorIV;
                break;
            case 5:
                pSecondRotor=pRotorV;
                break;
            case 6:
                pSecondRotor=pRotorVI;
                break;
            case 7:
                pSecondRotor=pRotorVII;
                break;
            case 8:
                pSecondRotor=pRotorVIII;
                break;
            
            default:
                break;
            }

            switch (thirdRotor)
            {
            case 1:
                pThirdRotor=pRotorI;
                break;
            case 2:
                pThirdRotor=pRotorII;
                break;
            case 3:
                pThirdRotor=pRotorIII;
                break;
            case 4:
                pThirdRotor=pRotorIV;
                break;
            case 5:
                pThirdRotor=pRotorV;
                break;
            case 6:
                pThirdRotor=pRotorVI;
                break;
            case 7:
                pThirdRotor=pRotorVII;
                break;
            case 8:
                pThirdRotor=pRotorVIII;
                break;
            
            default:
                break;
            }

            useEnigma(userOption,pReflector,initialReflector,pFirstRotor,initialFirstRotor,pSecondRotor,initialSecondRotor,pThirdRotor,initialThirdRotor);
        
        }

        //encrypt message
        void useEnigma(int userOption,const int* userReflector,int positionReflector,const int* userFirstRotor,int positionFirstRotor,const int* userSecondRotor,int positionSecondRotor,const int* userThirdRotor,int positionThirdRotor){
            string message{};
            string encryptedMessage{};

            int reflector[26];
            int firstRotor[26];
            int secondRotor[26];
            int thirdRotor[26];

            //get rotors selected by the user
            for (size_t i = 0; i < 26; i++)
            {
                reflector[i]=*userReflector;
                userReflector++;
            }

            for (size_t i = 0; i < 26; i++)
            {
                firstRotor[i]=*userFirstRotor;
                userFirstRotor++;
            }

            for (size_t i = 0; i < 26; i++)
            {
                secondRotor[i]=*userSecondRotor;
                userSecondRotor++;
            }

            for (size_t i = 0; i < 26; i++)
            {
                thirdRotor[i]=*userThirdRotor;
                userThirdRotor++;
            }

            // Set initial positions of the rotors
            for (int i = 0; i < positionReflector; i++) {
                moveArrayRight(reflector, 26);
            }
            for (int i = 0; i < positionFirstRotor; i++) {
                moveArrayRight(firstRotor, 26);
            }
            for (int i = 0; i < positionSecondRotor; i++) {
                moveArrayRight(secondRotor, 26);
            }
            for (int i = 0; i < positionThirdRotor; i++) {
                moveArrayRight(thirdRotor, 26);
            }
            
            //user insert message
            cout<<endl<<endl<<"Enter your message (do not use symbols, only use letters and spaces):"<<endl;
            cin.ignore();  // Ignore any previous newline character
            getline(cin, message);  // Read the entire line, including spaces

            // Remove spaces from the message
            message.erase(remove(message.begin(), message.end(), ' '), message.end());

            // Convert the message to uppercase
            transform(message.begin(), message.end(), message.begin(), [](unsigned char c) { return toupper(c); });

            //encrypt message
            for (size_t i = 0; i < message.length(); i++)
            {
                char letter=message[i];
                char encryptedLetter{};
                int indexABC{};

                //search index of letter
                for (int j = 0; j < 26; j++) {
                    if (abc[j] == letter) {
                        indexABC = j;
                        break;
                    }
                }
                
                //the circuit goes like this, user input one letter, we search in rotor one what letter is in its place and we send it to the second rotor
                //the second rotor receives the letter from the first rotor, and send a new one to the third
                //the third rotor sends to the reflector another letter, the reflector sends a new letter back to the third rotor and so the cycle goes backwards until the output

                int firstResult=firstRotor[indexABC];
                int secondResult=secondRotor[firstResult];
                int thirdResult=thirdRotor[secondResult];
                int reflectorResult=reflector[thirdResult];

                int indexThirdRotor{};
                for (int j = 0; j < 26; j++) {
                    if (thirdRotor[j] == reflectorResult) {
                        indexThirdRotor = j;
                        break;
                    }
                }

                int indexSecondRotor{};
                for (int j = 0; j < 26; j++) {
                    if (secondRotor[j] == indexThirdRotor) {
                        indexSecondRotor = j;
                        break;
                    }
                }

                int indexFirstRotor{};
                for (int j = 0; j < 26; j++) {
                    if (firstRotor[j] == indexSecondRotor) {
                        indexFirstRotor = j;
                        break;
                    }
                }

                encryptedLetter=abc[indexFirstRotor];

                encryptedMessage=encryptedMessage+encryptedLetter;

                moveArrayRight(firstRotor, 26);
                if (positionFirstRotor == 25) {
                    moveArrayRight(secondRotor, 26);
                    if (positionSecondRotor == 25) {
                        moveArrayRight(thirdRotor, 26);
                    }
                }
                
            }

            cout<<endl<<"Your message is:";
            cout<<endl<<encryptedMessage;
            cout<<endl;
            cout<<endl<<"Remember to send the rotors numbers, reflector number, and the initial positions of all of them to the receiver so he can decrypt the message.";
            
        }

        void moveArrayRight(int arr[], int size) {
            int lastElement = arr[size - 1];
            for (int i = size - 1; i > 0; i--) {
                arr[i] = arr[i - 1];
            }
            arr[0] = lastElement;
        }
};

int main(){

    enigma enigma;

    enigma.menu();

    return 0;
}

