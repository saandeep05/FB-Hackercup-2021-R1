#include<bits/stdc++.h>

struct Node{
    char data;
    char letter;
    int frequency;
    Node* next;
};
int T; // no of birthdays => number of strings;

bool isVowel(char letter){
    if(letter == 'A'||letter == 'E'||letter == 'I'||letter == 'O'||letter == 'U'){
        return true;
    }
    return false;
}

Node* createNewNode(char letter){
    Node* newNode = new Node();
    newNode->data = letter;
    if(isVowel(letter)){
        newNode->letter = 'v';
    }
    else{
        newNode->letter = 'c';
    }
    newNode->next = NULL;
    return newNode;
}

bool isPresentInLetters(char letter,Node** letters,int index){
    Node* ptr = letters[index];
    while(ptr!=NULL){
        if(letter == ptr->data){
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

int highestVowelOccurence(int index,Node** letters){
    Node* ptr = letters[index];
    int maxOccurence = 0;
    while(ptr!=NULL){
        if(ptr->letter == 'v'){
            if(ptr->frequency >= maxOccurence){
                maxOccurence = ptr->frequency;
            }
        }
        ptr = ptr->next;
    }
    return maxOccurence;
}

int highestConsonantOccurence(int index,Node** letters){
    Node* ptr = letters[index];
    int maxOccurence = 0;
    while(ptr!=NULL){
        if(ptr->letter == 'c'){
            if(ptr->frequency >= maxOccurence){
                maxOccurence = ptr->frequency;
            }
        }
        ptr = ptr->next;
    }
    return maxOccurence;
}

int totalVowelOccurance(int index,Node** letters){
    Node* ptr = letters[index];
    int totalOccurance = 0;
    while(ptr!=NULL){
        if(ptr->letter == 'v'){
            totalOccurance += ptr->frequency;
        }
        ptr = ptr->next;
    }
    return totalOccurance;
}

int totalConsonantOccurance(int index,Node** letters){
    Node* ptr = letters[index];
    int totalOccurance = 0;
    while(ptr!=NULL){
        if(ptr->letter == 'c'){
            totalOccurance += ptr->frequency;
        }
        ptr = ptr->next;
    }
    return totalOccurance;
}

void minNumberOfSecondsToMakeStringConsistent(std::string* S,Node** letters){
    int* highestVowel = new int[T]; //vowel with highest frequency in the string;
    int* highestConsonant = new int[T]; //consonant with highest frequency in the string;
    int* totalVowel = new int[T]; //total occurences of vowels in the string;
    int* totalConsonant = new int[T]; //total occurences of consonants in the string;

    for(int i=0;i<T;i++){
        std::string currentString = S[i];
        for(int j=0;j<currentString.length();j++){
            int count = 0;
            if(isPresentInLetters(currentString[j],letters,i)){
                continue;
            }
            for(int k=0;k<currentString.length();k++){
                if(currentString[k] == currentString[j]){
                    count++;
                }
            }
            Node* newNode = createNewNode(currentString[j]);
            if(letters[i] == NULL){
                newNode->frequency = count;
                letters[i] = newNode;
            }
            else{
                Node* ptr = letters[i];
                while(ptr->next!=NULL){
                    ptr = ptr->next;
                }
                newNode->frequency = count;
                ptr->next = newNode;
            }
        }
        highestVowel[i] = highestVowelOccurence(i,letters);
        highestConsonant[i] = highestConsonantOccurence(i,letters);
        totalVowel[i] = totalVowelOccurance(i,letters);
        totalConsonant[i] = totalConsonantOccurance(i,letters);
        int vowelCaseTime = 2*(totalVowel[i] - highestVowel[i]) + totalConsonant[i];
        int consonantCaseTime = 2*(totalConsonant[i] - highestConsonant[i]) + totalVowel[i];

        if(vowelCaseTime < consonantCaseTime){
            std::cout << "Case #" << i+1 << ": " << vowelCaseTime << std::endl;
        }
        else{
            std::cout << "Case #" << i+1 << ": " << consonantCaseTime << std::endl;
        }
    }
}

int main(){
    freopen("./consistency_chapter_1_input/consistency_chapter_1_input.txt", "r", stdin);
    freopen("final_output.txt", "w", stdout);

    std::cin >> T;
    Node** letters = new Node*[T];
    std::string* S = new std::string[T]; //Array is preferred because only accessing is required for this problem
    for(int i=0;i<T;i++){
        std::cin >> S[i];
        *(letters+i) = NULL;
    }
    minNumberOfSecondsToMakeStringConsistent(S,letters);
    return 0;
}
