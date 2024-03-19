/*
 * FCAI-CU – Structured Programming – 2024 - Assignment 2 - Task 4
 * Program Name: CS112_A2_T4_S17_S18_20230586_20230461_20230584.cpp
 * Program Description: This is a program that takes a message from the user and encrypts/decrypts it
                        using a cipher algorithm. The user could choose which cipher type he wants to use.
                        Cipher types included are: Affine Cipher - Route Cipher - Atbash Cipher - Vignere Cipher -
                        Baconian Cipher - Simple Substitution Cipher - Polybius Square- Morse Code - XOR Cipher -
                        Rail-fence Cipher


 * Last Modification Date: 19/3/2024

 * Author1 and ID and Group: Helana Wageh Edward Soltan, 20230461, S17
 * Author2 and ID and Group: Malak Reda Mohamed Esmail, 20230584, S18
 * Author3 and ID and Group: Salsabil Bahaaeldin Rohaiem Mohamed, 20230586, S18

 * Teaching Assistant: Eng. Ahmed Lotfy
 * Who did what: Helana did abtash, simple substitution Cipher, and Route cipher. Malak did Vignere, affine, baconian, and Rail-fence Cipher. Salsabil did Morse code,
   polybius Square, and XOR Cipher
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <regex>

using namespace std;

// function to encrypt a message using affine cipher
string cipher(string mess1, int a, int b) {
    string ciphermess1 = "";

    for (char& c : mess1) {
        if (isalpha(c)) {
            int x = toupper(c) - 'A'; // Convert each letter to uppercase and map into its numeric value
            int ciphered_lett = (a * x + b) % 26; // Encryption function
            if (ciphered_lett < 0) {
                ciphered_lett += 26; // Ensure positive value
            }
            ciphermess1 += char(ciphered_lett + 'A'); // Convert back to corresponding letter
        } else {
            ciphermess1 += c;
        }
    }
    return ciphermess1;
}

// Function to calculate modular multiplicative inverse
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Function to decrypt ciphered message using Affine Cipher
string decipher(string mess2, int a, int b) {
    string ciphermess2 = "";

    int a_inv = modInverse(a, 26); // Calculate modular multiplicative inverse of integer a

    for (char& c : mess2) {
        if (isalpha(c)) {
            int y = toupper(c) - 'A'; // Convert each letter to uppercase and map into its numeric value
            int deciphered_lett = (a_inv * (y - b)) % 26; // Decryption function
            if (deciphered_lett < 0) {
                deciphered_lett += 26;
            }
            ciphermess2 += char(deciphered_lett + 'A'); // Convert back to corresponding letter
        } else {
            ciphermess2 += c;
        }
    }
    return ciphermess2;
}


int affine(){
    int choice;
    // Display menu options
    cout << "1. Cipher a message\n" << "2. Decipher a message\n" << "3. End\n";

    // Take user input for choice
    cin >> choice;
    cin.ignore(); // Ignore the newline character in the input buffer

    // Take actions based on user's choice

    if (choice == 1) {
        // Encrypt a message
        int a, b;
        string mess1;

        cout << "Enter parameter1: ";
        cin >> a;

        cout << "Enter parameter2: ";
        cin >> b;

        int a_inv = modInverse(a, 26);
        if ( (a * a_inv) % 26 != 1){
            cout << "Invalid input! please enter a valid parameter";
        }

        else {
            cout << "Enter your message:\n";

            cin.ignore(); // Ignore the newline character in the input buffer
            getline(cin, mess1); // Read the input message

            string ciphermess1 = cipher(mess1, a, b); // Encrypt the message
            cout << "The Affine ciphered message is: " << ciphermess1 << "\n"; // Display the encrypted message
        }

        return 0;
    }

        else if (choice == 2) {
        // Decrypt a message
        int a, b;

        string mess2;
        cout << "Enter parameter1: ";
        cin >> a;

        cout << "Enter parameter2: ";
        cin >> b;

        int a_inv = modInverse(a, 26);
        if ( (a * a_inv) % 26 != 1){
            cout << "Invalid input! please enter a valid parameter";
        }

        else {
            cout << "Enter your message:\n";

            cin.ignore(); // Ignore the newline character in the input buffer
            getline(cin, mess2); // Read the input message

            string decip = decipher(mess2, a, b); // Decrypt the message
            cout << "The Affine deciphered message is: " << decip << "\n"; // Display the decrypted message
        }

    }

        else if (choice == 3) {
        // End the program
        cout << "Thanks!\n";
    }

        else {
        // Invalid choice
        cout << "Invalid Choice! Please choose a number from the menu.\n";
    }
    return 0;
}

// Function to encrypt a string using Route Cipher
string transformMessageRoute(const string& message, int key) {
    /* Clean up the message by removing non-alphabetic characters and converting to uppercase*/
    string cleanedMessage;
    for (char character : message) {
        if (isalpha(character)) {
            cleanedMessage += toupper(character);
        }
    }

    /* Determine the number of rows in the grid*/
    int numRows = cleanedMessage.length() / key + (cleanedMessage.length() % key != 0);

    /*Create a grid to store the transformed message*/
    vector<string> grid(numRows, string(key, 'X'));
    int index = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < key && index < cleanedMessage.length(); j++) {
            grid[i][j] = cleanedMessage[index++];
        }
    }

    /* Rearrange the characters in a spiral pattern starting from the top right corner*/
    string transformedMessage;
    int top = 0, bottom = numRows - 1, left = 0, right = key - 1;
    int direction = 0; // 0: right, 1: down, 2: left, 3: up
    while (top <= bottom && left <= right) {
        if (direction == 0) {
            for (int i = top; i <= bottom; i++) {
                if (grid[i][right] != 'X') {
                    transformedMessage += grid[i][right];
                }
            }
            right--;
            direction = 1;
        } else if (direction == 1) {
            for (int i = right; i >= left; i--) {
                if (grid[bottom][i] != 'X') {
                    transformedMessage += grid[bottom][i];
                }
            }
            bottom--;
            direction = 2;
        } else if (direction == 2) {
            for (int i = bottom; i >= top; i--) {
                if (grid[i][left] != 'X') {
                    transformedMessage += grid[i][left];
                }
            }
            left++;
            direction = 3;
        } else if (direction == 3) {
            for (int i = left; i <= right; i++) {
                if (grid[top][i] != 'X') {
                    transformedMessage += grid[top][i];
                }
            }
            top++;
            direction = 0;
        }
    }

    return transformedMessage;
}

// Function to decrypt a string using Route Cipher
string decodeMessageRoute(const string& message, int key) {
    /* Determine the number of rows in the grid */
    int numRows = message.length() / key + (message.length() % key != 0);

    /* Create a grid to store the decoded message */
    vector<string> grid(numRows, string(key, 'X'));
    int index = 0;
    int top = 0, bottom = numRows - 1, left = 0, right = key - 1;
    int direction = 0; // 0: right, 1: down, 2: left, 3: up
    while (top <= bottom && left <= right) {
        if (direction == 0) {
            for (int i = top; i <= bottom; i++) {
                if (index < message.length()) {
                    grid[i][right] = message[index++];
                }
            }
            right--;
            direction = 1;
        } else if (direction == 1) {
            for (int i = right; i >= left; i--) {
                if (index < message.length()) {
                    grid[bottom][i] = message[index++];
                }
            }
            bottom--;
            direction = 2;
        } else if (direction == 2) {
            for (int i = bottom; i >= top; i--) {
                if (index < message.length()) {
                    grid[i][left] = message[index++];
                }
            }
            left++;
            direction = 3;
        } else if (direction == 3) {
            for (int i = left; i <= right; i++) {
                if (index < message.length()) {
                    grid[top][i] = message[index++];
                }
            }
            top++;
            direction = 0;
        }
    }
    /* Concatenate characters in the grid to form the decoded message */
    string transformedMessage;
    for (const string& row : grid) {
        for (char c : row) {
            if (c != 'X') {
                transformedMessage += c;
            }
        }
    }
    return transformedMessage; // Return the decoded message
}

int route(){
    char choice;
    string message;

    cout << "Welcome to Route Cipher Program!" << endl;

    /* Prompt the user for their choice*/
    cout << "Do you want to encode (E) or decode (D) a message? ";
    cin >> choice;

    /* Ignore any remaining characters in the input buffer*/
    cin.ignore();

    /* Perform the selected operation*/
    if (toupper(choice) == 'E') {
        /*Encoding*/
        cout << "Please enter the message to encode: ";
        getline(cin, message);

        /*Set the transformation key*/
        int key = 3;

        /*Transform the message*/
        string transformedMessage = transformMessageRoute(message, key);

        /* Display the encoded message*/
        cout << "Encoded message: " << transformedMessage << endl;
    } else if (toupper(choice) == 'D') {
        cout << "Please enter the message to decode: ";
        getline(cin, message);
        int key = 3;
        cout << "Decoded message: " << decodeMessageRoute(message, key) << endl;

    } else {
        /* Invalid choice*/
        cout << "Invalid selection. The Program Will Close Now." << endl;
    }

    return 0;
}

/* A function that executes the Atbash Cipher algorithm on the text being passed*/
string atbashCipher(const string& Text) {
    string cipherText = Text;

    for (char& c : cipherText) {
        if (isalpha(c)) {
            if (isupper(c)) {
                c = 'Z' - (c - 'A'); /* Replace the capital letter with a conjugate letter in the alphabet*/
            } else {
                c = 'z' - (c - 'a'); /* Replace lowercase letter with a companion letter in the alphabet*/
            }
        }
    }

    return cipherText;
}

/*A function that performs encryption using the specified halves of the alphabet*/
string encryptText(const string& text, const string& firstHalfAlphabet, const string& secondHalfAlphabet) {
    string encryptedText = text;

    transform(encryptedText.begin(), encryptedText.end(), encryptedText.begin(), ::toupper); // تحويل النص إلى أحرف كبيرة

    for (char& c : encryptedText) {
        if (isalpha(c)) {
            if (c >= 'A' && c <= 'M') {
                size_t index = c - 'A';
                c = firstHalfAlphabet[index]; /* Replace the letter using the first half of the alphabet*/
            } else if (c >= 'N' && c <= 'Z') {
                size_t index = c - 'N';
                c = secondHalfAlphabet[index]; /* Replace the letter using the second half of the alphabet*/
            }
        }
    }

    return encryptedText;
}

int Atbash(){
    cout<<"Welcome to Atbash Cipher\n";
    cout << "Enter a message: ";
    string text;
    getline(cin, text);

    cout << "Choice operation:\n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;


    string transformedMessage;

    switch (choice) {
        case 1:
            transformedMessage = atbashCipher(text); // تشفير النص باستخدام خوارزمية Atbash Cipher
            cout << "Encrypted message: " << transformedMessage << endl;
            break;
        case 2:
            transformedMessage = atbashCipher(text); // فك تشفير النص باستخدام خوارزمية Atbash Cipher
            cout << "Decrypted message: " << transformedMessage << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }

    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string firstHalfAlphabet = alphabet.substr(0, alphabet.length() / 2);
    string secondHalfAlphabet = alphabet.substr(alphabet.length() / 2);

    string plainText;
    cout << "Enter the text to encrypt: ";
    getline(cin, plainText);

    string encryptedText = encryptText(plainText, firstHalfAlphabet, secondHalfAlphabet); // تشفير النص باستخدام النصفين المحددين من الأبجدية

    cout << "Encrypted text: " << encryptedText << endl;
}

string generateCipherAlphabet(const string& key) {
    unordered_map<char, bool> TakenLet;
    string cipherAlphabet;

    for (char let : key) {
        let = tolower(let);
        if (TakenLet.count(let) == 0) {
            TakenLet[let] = true;
            cipherAlphabet.push_back(let);
        }
    }

    for (char let = 'a'; let <= 'z'; ++let) {
        if (TakenLet.count(let) == 0) {
            cipherAlphabet.push_back(let);
        }
    }

    return cipherAlphabet;
}

string simpleSubstitutionencrypt(const string& message, const string& cipherAlphabet) {
    string encryptedMessage;

    for (char let : message) {
        let = tolower(let);

        if (isalpha(let)) {
            size_t index = let - 'a';
            if (index < cipherAlphabet.length()) {
                encryptedMessage.push_back(cipherAlphabet[index]);
            }
        } else {
            encryptedMessage.push_back(let);
        }
    }

    return encryptedMessage;
}

// Vignere Cipher
string message;
string mappedKey;

void messageAndKey(){
    string msg;
    cout << "Enter your message: ";
    getline(cin, msg);
    cin.ignore();

    //message to uppercase
    for(int i = 0; i < msg.length(); i++){
        msg[i] = toupper(msg[i]);
    }

    string key;
    cout << "Enter the keyword: ";
    getline(cin, key);
    cin.ignore();

    //key to uppercase
    for(int i = 0; i < key.length(); i++){
        key[i] = toupper(key[i]);
    }

    //mapping key to message
    string keyMap = "";
    for (int i = 0,j = 0; i <msg.length();i++){
        if(msg[i] ==32){
            keyMap += 32;
        } else {
            if(j<key.length()){
                keyMap += key[j];
                j++;
            } else {
                j = 0;
                keyMap += key[j];
                j++;
            }
        }
    }
    message = msg;
    mappedKey = keyMap;
}

int alphabet[26][26];
void VigenereTable(){
    for (int i = 0; i < 26; i++){
        for (int j = 0; j < 26; j++){
            int temp;
            if((i+65)+j > 90){
                temp = ((i+65)+j) - 26;

                //adding ASCII of alphabet letter in table index position
                alphabet[i][j] = temp;
            } else {
                temp = (i+65)+j;

                //adding ASCII of alphabet letter in table index position
                alphabet[i][j] = temp;
            }
        }
    }
}

void vignerecipher(string message, string mappedKey){
    VigenereTable();
    string cipheredmess = "";
    for(int i = 0; i < message.length(); i++){
        if(message[i] == 32 && mappedKey[i] == 32){
            cipheredmess += " ";
        } else {
            int x = (int)message[i]-65;
            int y = (int)mappedKey[i]-65;
            cipheredmess += (char)alphabet[x][y];
        }
    }

    cout << "The vignere ciphered message is: \n" << cipheredmess;
}

int itrCount(int key, int msg){
    int counter = 0;
    string result = "";

    //starting from ASCII of letter of Key and ending at letter of message
    // to get full 26 letters of alphabet
    for(int i = 0; i < 26; i++){
        if(key+i > 90){
            result += (char)(key+(i-26));
        } else {
            result += (char)(key+i);
        }
    }

    for(int i = 0; i < result.length(); i++){
        if(result[i] == msg){
            break;
        } else {
            counter++;
        }
    }
    return counter;
}

void vigneredecipher(string message, string mappedKey){
    string decipheredmess = "";
    for(int i = 0; i < message.length(); i++){
        if(message[i] == 32 && mappedKey[i] == 32){
            decipheredmess += " ";
        } else {
            int temp = itrCount((int)mappedKey[i], (int)message[i]);
            decipheredmess += (char)(65+temp);
        }
    }

    cout << "The Vegnere deciphered message is: \n" << decipheredmess;
}

void vignere(){
    int choice;
    cout << "1. Encryption\n2. Decryption\n3. End\n ";
    cin >> choice;
    cin.ignore();

    if (choice == 1){
        messageAndKey();
        vignerecipher(message, mappedKey);

    } else if (choice == 2){
        messageAndKey();
        vigneredecipher(message, mappedKey);

    }
    else if (choice == 3){
        cout << "Thanks!";
    }
    else {
        cout << "Invalid Input! you should choose a number from the menu\n";
    }
}

// Function to encrypt a string using Baconian Cipher
string encryptBaconianCipher(string mess1) {

    // Define key and value arrays for encryption
    string key[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P",
                      "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    string value[26] = {"aaaaa", "aaaab", "aaaba", "aaabb", "aabaa", "aabaa", "aabba", "aabbb", "abaaa",
                        "abaab", "ababa", "ababb", "abbaa", "abbab", "abbba", "abbbb", "baaaa", "baaab", "baaba", "baabb",
                        "babaa", "babab", "babba", "babbb", "bbaaa", "bbaab"};
    string ciphermess1 = "";

    // Encrypt each character in the input string
    for (char m : mess1) {
        if (isalpha(m)) {
            // Convert lowercase characters to uppercase
            if (islower(m))
                m = toupper(m);
            // Find index of the character in the key array and append corresponding value to the output string
            int index = m - 'A';
            ciphermess1 += value[index];
        } else {
            // Non-alphabetic characters remain unchanged
            ciphermess1 += m;
        }
    }
    return ciphermess1;
}

// Function to decrypt a string using Baconian Cipher
string decryptBaconianCipher(string mess2) {

    // Define key and value arrays for decryption
    string value[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P",
                        "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    string key[26] = {"aaaaa", "aaaab", "aaaba", "aaabb", "aabaa", "aabaa", "aabba", "aabbb", "abaaa",
                      "abaab", "ababa", "ababb", "abbaa", "abbab", "abbba", "abbbb", "baaaa", "baaab", "baaba", "baabb",
                      "babaa", "babab", "babba", "babbb", "bbaaa", "bbaab"};
    string decip = "";

    // Decrypt the message in blocks of 5 characters
    for (int i = 0; i < mess2.length(); i += 5) {
        for (int j = 0; j < 26; j++) {
            // Check if the current block matches any value in the key array
            if (key[j] == mess2.substr(i, 5)) {
                // Append the corresponding character from the value array to the output string
                decip += value[j];
                break;
            }
        }
    }
    return decip;
}

int baconian(){
    int choice;

    while (true){
        // Display menu options
        cout << "1. Cipher a message\n" << "2. Decipher a message\n";
        // Take user input for choice
        cin >> choice;
        cin.ignore(); // Ignore the newline character in the input buffer

        // Take actions based on user's choice
        if (choice == 1) {
            // Encrypt a message
            string mess1;
            cout << "Enter your message:\n";
            getline(cin, mess1); // Read the input message
            string ciphermess1 = encryptBaconianCipher(mess1); // Encrypt the message
            cout << "The Baconian ciphered message is: " << ciphermess1 << endl;
            break;
        }
        else if (choice == 2) {
            // Decrypt a message
            string mess2;
            cout << "Enter your message:\n";
            getline(cin, mess2); // Read the input message
            string decip = decryptBaconianCipher(mess2); // Decrypt the message
            cout << "The Baconian deciphered message is: " << decip << endl;
            break;
        }
        else {
            // Invalid choice
            cerr << "Invalid Choice! Please choose a number from the menu.\n";
        }
    }
    return 0;
}

// simple substitution cipher
string simpleSubstitutiondecrypt(const string& encryptedMessage, const string& cipherAlphabet) {
    string decryptedMessage;

    for (char let : encryptedMessage) {
        let = tolower(let);

        if (isalpha(let)) {
            size_t index = cipherAlphabet.find(let);
            if (index != string::npos) {
                decryptedMessage.push_back('a' + index);
            }
        } else {
            decryptedMessage.push_back(let);
        }
    }

    return decryptedMessage;
}

void simpleSubstitution(){
    string key;
    string message;
    string choice;

    cout << "Welcome to Simple Substitution Cipher.\n";
    cout << "Choice operation:\n";
    cout << "E. Encrypt\n";
    cout << "D. Decrypt\n";
    cout << "Enter your choice: ";
    cin >> choice;

    while (true) {
        cout << "Enter the key (maximum of five characters): ";
        cin >> key;

        if (key.length() <= 5) {
            break;
        }

        cout << "Invalid key. Please enter a key with a maximum of five characters." << endl;
    }

    cout << "Enter the message: ";
    cin.ignore();
    getline(cin, message);

    string cipherAlphabet = generateCipherAlphabet(key);

    if (choice == "E" || choice == "e") {
        string encryptedMessage = simpleSubstitutionencrypt(message, cipherAlphabet);
        cout << "Encrypted message: " << encryptedMessage << endl;
    } else if (choice == "D" || choice == "d") {
        string decryptedMessage = simpleSubstitutiondecrypt(message, cipherAlphabet);
        cout << "Decrypted message: " << decryptedMessage << endl;
    } else {
        cout << "Invalid choice. Please enter 'E' to encrypt or 'D' to decrypt." << endl;
    }

}

// Function to encrypt text using a Polybius square cipher
string encryptPolybiusSquare(string text, string letters[5][5], int key[5]) {
    string encrypted;

    // Iterate through each character in the text
    for (char ch : text) {
        // If the character is a space, append it to the encrypted string and continue to the next character
        if (ch == ' ') {
            encrypted += ' ';
            continue;
        }
            // If the character is an alphabet character, find its corresponding cipher in the Polybius square
        else if (isalpha(ch)) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (toupper(ch) == letters[i][j][0]) {
                        // Append the key representing the row and column of the character in the Polybius square
                        encrypted += to_string(key[i]) + to_string(key[j]);
                    }
                }
            }
        }
    }
    return encrypted;
}

// Function to decrypt cipher text with a Polybius square cipher
string decryptPolybiusSquare(string text, string letters[5][5], int key[5]) {
    string decrypted;

    // Iterate through the encrypted text two characters at a time
    for (int i = 0; i < text.size() - 1; i += 2) {
        // If the character is a space, append it to the decrypted string and move to the next character
        if (text[i] == ' ') {
            decrypted += ' ';
            i++;
        }
        if (isdigit(text[i]) && isdigit(text[i + 1]))
        {
            int row = -1, col = -1;
            // Find the row and column index corresponding to the key
            for (int r = 0; r < 5; r++) {
                for (int c = 0; c < 5; c++) {
                    if (key[r] == (text[i] - '0') && key[c] == (text[i + 1] - '0')) {
                        row = r;
                        col = c;
                        break;
                    }
                }
                if (row != -1) break; // If found, break the outer loop
            }
            // If valid row and column found, append the corresponding letter
            if (row != -1 && col != -1)
                decrypted += letters[row][col][0];
        }
    }
    return decrypted;
}

int polybiusSquare(){
    int choice;
    string message;
    int key[5];
    string letters[5][5] = {
            {"A", "B", "C", "D", "E"},
            {"F", "G", "H", "I/J", "K"},
            {"L", "M", "N", "O", "P"},
            {"Q", "R", "S", "T", "U"},
            {"V", "W", "X", "Y", "Z"}
    };

        cout << "Enter the key of numbers (1-5): " << endl;
        for (int i = 0; i < 5; i++) {
            cin >> key[i];

            // Input validation: check if the entered number is within the range (1-5)
            while (key[i] > 5 || key[i] < 1) {
                cerr << "Please enter a number between (1-5)\n";
                cin >> key[i];
            }

            // Check if the entered number is unique
            for (int j = 0; j < i; j++) {
                if (key[i] == key[j]) {
                    cerr << "Please enter a unique number\n";
                    i--; // Decrement i to re-enter the same index
                    break; // Exit the loop as soon as a duplicate is found
                }
            }
        }


    while (true){
        cout << "What do you want to do? (Choose 1 or 2) " << endl;
        cout << "1- Cipher a message " << endl;
        cout << "2- Decipher a message " << endl;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Please enter plain text to encrypt: " << endl;
            getline(cin, message);
            cout << "Cipher text: " << encryptPolybiusSquare(message, letters, key) << endl;
            break;
        }
        else if (choice == 2) {
            cout << "Please enter cipher text to decrypt: " << endl;
            getline(cin, message);
            cout << "Plain text: " << decryptPolybiusSquare(message, letters, key) << endl;
            break;
        }
        else {
            cerr << "Invalid choice! Please enter 1 or 2.";
        }
    }
    return 0;
}

// A function to check if a Morse code message contains valid characters ('-', '.', ' ').
bool isValidMorse (string message){
    for (char ch : message) {
        if (ch != '-' && ch != '.' && ch != ' ')
            return false;
    }
    return true;
}

// A function to create a map of characters to Morse code and vice versa.
pair<map<char, string>, map<string, char>> morseMap() {
    // Mapping of each character to its Morse code.
    map<char, string> charToMorse;
    map<string, char> morseToChar;

    charToMorse['A'] = ".-";
    charToMorse['B'] = "-...";
    charToMorse['C'] = "-.-.";
    charToMorse['D'] = "-..";
    charToMorse['E'] = ".";
    charToMorse['F'] = "..-.";
    charToMorse['G'] = "--.";
    charToMorse['H'] = "....";
    charToMorse['I'] = "..";
    charToMorse['J'] = ".---";
    charToMorse['K'] = "-.-";
    charToMorse['L'] = ".-..";
    charToMorse['M'] = "--";
    charToMorse['N'] = "-.";
    charToMorse['O'] = "---";
    charToMorse['P'] = ".--.";
    charToMorse['Q'] = "--.-";
    charToMorse['R'] = ".-.";
    charToMorse['S'] = "...";
    charToMorse['T'] = "-";
    charToMorse['U'] = "..-";
    charToMorse['V'] = "...-";
    charToMorse['W'] = ".--";
    charToMorse['X'] = "-..-";
    charToMorse['Y'] = "-.--";
    charToMorse['Z'] = "-..-";
    charToMorse['!'] = "-.-.--";
    charToMorse['@'] = ".--.-.";
    charToMorse['$'] = "...-..-";
    charToMorse['&'] = ".-...";
    charToMorse['('] = "-.--.";
    charToMorse[')'] = "-.--.-";
    charToMorse['-'] = "-....-";
    charToMorse['_'] = "..--.-";
    charToMorse['+'] = ".-.-.";
    charToMorse['='] = "-...-";
    charToMorse['/'] = "-..-.";
    charToMorse['?'] = "..--..";
    charToMorse['"'] = ".-..-.";
    charToMorse[';'] = "-.-.-.";
    charToMorse['0'] = "-----";
    charToMorse['1'] = ".----";
    charToMorse['2'] = "..---";
    charToMorse['3'] = "...--";
    charToMorse['4'] = "....-";
    charToMorse['5'] = ".....";
    charToMorse['6'] = "-....";
    charToMorse['7'] = "--...";
    charToMorse['8'] = "---..";
    charToMorse['9'] = "----.";

    // Create reverse map (Morse code to character)
    for (const auto& pair : charToMorse) {
        morseToChar[pair.second] = pair.first;
    }

    return {charToMorse, morseToChar};
}

void morseCode (){
    // Create maps
    auto maps = morseMap();
    map<char, string> charToMorse = maps.first;
    map<string, char> morseToChar = maps.second;

    while (true){
        string choice;
        cout << "Welcome to Morse Code cipher! Choose 1 or 2\n";
        cout << "1) Cipher a message.\n";
        cout << "2) Decipher a message.\n";
        cin >> choice;
        cin.ignore();

        // Map characters to its Morse Code.
        if (choice == "1") {

            string message, encrypted, decrypted;
            cout << "Enter the message:";
            getline(cin, message);

            for (char i : message) {
                if (i == ' '){
                    encrypted += "   ";
                } else {
                    encrypted += charToMorse[toupper(i)] + ' ';
                }
            }
            cout << "The ciphered text:" << encrypted << endl;
            break;
        }

            // Map Morse Code to its character.
        else if (choice == "2") {

            string message, encrypted, decrypted;
            cout << "Enter the message:";
            getline(cin, message);

            // Validate Morse code input.
            while (!isValidMorse(message)){
                cout << "Invalid input. Please enter a new message:";
                getline(cin, message);
            }
            string substr;
            for (int i = 0; i < message.size(); i++) {
                if (message[i] != ' ') {
                    substr += message[i];
                } else if (message[i] == ' '){
                    decrypted += morseToChar[substr];
                    substr = "";
                    if (message[i+1] == ' ' && message[i+2] == ' '){
                        decrypted += ' ';
                        i += 3;
                    }
                }
            }

            // Append the last character after the loop.
            if (!substr.empty()) {
                decrypted += morseToChar[substr];
            }

            cout << "The deciphered text:" << decrypted << endl;
            break;
        }


            // If the user entered a number rather than 1 or 2.
        else {
            cout << "Please enter 1 or 2." << endl;
        }
    }

}

// A function to convert a decimal number to hexadecimal number.
string decimalToHexadecimal(int num) {
    string hexChars = "0123456789ABCDEF";
    string hexaNum;
    while (num > 0) {
        int remainder = num % 16;
        hexaNum += hexChars[remainder];
        num /= 16;
    }
    if (hexaNum.empty())
        return "0";
    else {
        reverse(hexaNum.begin(), hexaNum.end());
        return hexaNum;
    }
}

// A function to convert a hexadecimal number to decimal number.
int hexaToDecimal(string num) {
    string hexChars = "0123456789ABCDEF";
    int decimalNum = 0;
    int power = 0;
    for (int i = num.size() - 1; i >= 0; --i) {
        char digit = num[i];
        decimalNum += hexChars.find(toupper(digit)) * pow(16, power);
        power++;
    }
    return decimalNum;
}

// A function to encrypt a message using XOR cipher.
void xorCipher(){
    string key, message;
    cout << "Enter the key:";
    cin >> key;
    cout << "Enter the message:";
    cin >> message;

    // Convert the key to ASCII values.
    int keyAscii[key.size()];
    for (int i = 0; i < key.size(); ++i){
        keyAscii[i] = (int) key[i];
    }
    int sz = message.size();
    int xorAscii[sz];
    int keyIndex = 0;
    // Apply XOR encryption.
    for (int i = 0; i < sz; ++i){
        xorAscii[i] = (int) message[i] ^ keyAscii[keyIndex];
        if (keyIndex < key.size() - 1)
            keyIndex++;
        else
            keyIndex = 0;
    }
    string xorText, xorHexa[sz];
    // Convert XORed ASCII values to hexadecimal.
    for (int i = 0; i < sz; ++i) {
        xorText += (char) xorAscii[i];
        xorHexa[i] = decimalToHexadecimal(xorAscii[i]);
    }
    cout << "Cipher text:" << xorText << endl;
    cout << "Hexa:";

    for (int i = 0; i < sz; ++i) {
        cout << xorHexa[i] << ' ';
    }
    cout << endl;
}

void xorDecipher (){
    string key, message;
    cout << "Enter the key:";
    cin >> key;
    cin.ignore(); // Clear newline character from the buffer.
    cout << "Enter the message:";
    getline(cin, message);

    // Convert the key to ASCII values.
    int keyAscii[key.size()];
    for (int i = 0; i < key.size(); ++i){
        keyAscii[i] = (int) key[i];
    }

    string substr;
    vector <string> hexaMessage = {};
    // Split the message into hexadecimal substrings.
    for (int i = 0; i < message.size(); ++i) {
        if (message[i] == ' '){
            hexaMessage.push_back(substr);
            substr = "";
        } else {
            substr += message[i];
        }
    }
    if (!substr.empty()) {
        hexaMessage.push_back(substr);
    }

    vector <int> xorAscii = {};
    int keyIndex = 0;
    // Apply XOR decryption.
    for (const auto & i : hexaMessage) {
        int num = hexaToDecimal(i) ^ keyAscii[keyIndex];
        xorAscii.push_back(num);
        if (keyIndex < key.size() - 1)
            keyIndex++;
        else
            keyIndex = 0;
    }
    string decrypted;
    // Convert decrypted ASCII values to characters.
    for (int i : xorAscii) {
        decrypted += (char) i;
    }
    cout << "Deciphered text:" << decrypted << endl;
}

void XOR(){
    while (true){
        string choice;
        cout << "Welcome to XOR cipher! Choose 1 or 2\n";
        cout << "1) Cipher a message.\n";
        cout << "2) Decipher a message.\n";
        cin >> choice;
        cin.ignore();

        if (choice == "1") {
            xorCipher();
            break;
        } else if (choice == "2") {
            xorDecipher();
            break;
        } else {
            cout << "Please enter 1 or 2." << endl;
        }
    }

}

// rail fence cipher
void railFencecipher(){
    string message;
    cout << "Enter the message: \n";
    getline(cin , message);
    cin.ignore();

    // removing white space from message
    message = regex_replace(message, regex("\\s+"), "");

    cout << "Enter key: \n";
    int key;
    cin >> key;
    cin.ignore();

    // creating empty matrix
    char railMatrix[key][message.length()];
    for (int i = 0; i < key; i++){
        for (int j = 0; j < message.length(); j++){
            railMatrix[i][j] = '.';
        }
    }

    // putting message letters one by one in rail matrix in zig-zag
    int row = 0;
    int check = 0;
    for (int i = 0; i < message.length(); i++){
        if (check == 0){
            railMatrix[row][i] = message[i];
            row++;
            if(row == key){
                check = 1;
                row--;
            }
        } else if (check == 1){
            row--;
            railMatrix[row][i] = message[i];
            if (row == 0){
                check = 0;
                row = 1;
            }
        }
    }

    string cipheredmess = "";
    for (int i = 0; i < key; i++){
        for (int j = 0; j < message.length(); j++){
            cipheredmess += railMatrix[i][j];
        }

    }
    cipheredmess = regex_replace(cipheredmess, regex("\\."), "");
    cout << "The Rail-Fence ciphered message is " << cipheredmess;
}

void railFencedecipher(){
    string message;
    cout << "Enter the ciphered message: \n";
    getline(cin , message);
    cin.ignore();

    // removing white space from message
    message = regex_replace(message, regex("\\s+"), "");

    cout << "Enter key: \n";
    int key;
    cin >> key;
    cin.ignore();

    // creating empty matrix
    char railMatrix[key][message.length()];
    for (int i = 0; i < key; i++){
        for (int j = 0; j < message.length(); j++){
            railMatrix[i][j] = '.';
        }
    }

    // putting message letters one by one in rail matrix in zig-zag
    int row = 0;
    int check = 0;
    for (int i = 0; i < message.length(); i++){
        if (check == 0){
            railMatrix[row][i] = message[i];
            row++;
            if(row == key){
                check = 1;
                row--;
            }
        } else if (check == 1){
            row--;
            railMatrix[row][i] = message[i];
            if (row == 0){
                check = 0;
                row = 1;
            }
        }
    }

    int ordr = 0;
    for (int i = 0; i < key; i++){
        for (int j = 0; j < message.length(); j++){
            string temp = "";
            temp += railMatrix[i][j];
            if(regex_match(temp, regex("\\."))){
                continue;
            } else {
                // adding cipher letters one by one diagonally
                railMatrix[i][j] = message[ordr];
                ordr++;
            }
        }
    }

    // converting rows back into a message of single line
    string decipheredmess = "";
    check = 0;
    row = 0;
    for (int i = 0; i < message.length(); i++){
        if (check == 0){
            decipheredmess += railMatrix[row][i];
            row++;
            if (row == key){
                check = 1;
                row--;
            }
        } else if (check == 1){
            row--;
            decipheredmess += railMatrix[row][i];
            if (row == 0){
                check = 0;
                row = 1;
            }
        }
    }
    decipheredmess = regex_replace(decipheredmess, regex("\\.+"), "");
    cout << "The Rail-Fence decipher message " << decipheredmess;
}

void railFence(){
    cout << "1. Encryption\n2. Decryption\n3. End\n ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1){
        railFencecipher();

    } else if (choice == 2) {
        railFencedecipher();

    }
    else if (choice == 3){
        cout << "Thanks!";
    }
    else {
        cout << "Invalid input! Please choose a number from the menu \n";
    }
}

int main() {
    string choice;

    while (true){
        cout << " \nWhich Cipher do you want to use? (Enter a number 1-11) " << endl;
        cout << "1- Affine Cipher " << endl;
        cout << "2- Route Cipher " << endl;
        cout << "3- Atbash Cipher " << endl;
        cout << "4- Vignere Cipher " << endl;
        cout << "5- Baconian Cipher " << endl;
        cout << "6- Simple Substitution Cipher " << endl;
        cout << "7- Polybius Square Cipher " << endl;
        cout << "8- Morse Cipher " << endl;
        cout << "9- XOR Cipher " << endl;
        cout << "10- Rail-Fence Cipher " << endl;
        cout << "11- End the program " << endl;
        cin >> choice;
        cin.ignore();

        if (choice == "1") {
            affine();
        }
        else if (choice == "2"){
            route();
        }
        else if (choice == "3"){
            Atbash();
        }
        else if (choice == "4"){
            vignere();
        }
        else if (choice == "5"){
            baconian();
        }
        else if (choice == "6"){
            simpleSubstitution();
        }
        else if (choice == "7"){
            polybiusSquare();
        }
        else if (choice == "8"){
            morseCode();
        }
        else if (choice == "9"){
            XOR();
        }
        else if (choice == "10"){
            railFence();
        }
        else if (choice == "11"){
            cout << "Exiting the program. Bye!";
            break;
        }
        else{
            cerr << "Please enter a valid choice" << endl;
        }

    }
    return 0;
}
