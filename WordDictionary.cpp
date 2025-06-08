#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct SuggestionNode{
    string word;
    SuggestionNode* next;


    SuggestionNode(string w) {
       word=w;
       next=nullptr;




       }


};




struct Node{
    string word;
    string meaning;
    Node* left;
    Node* right;


    Node(string w, string m){
        word=w;
        meaning =m;
        left=nullptr;
        right=nullptr;
    }
};




class Dictionary{
private:
    Node* root;


    Node* insert(Node* root, string word, string meaning ){
        if(root== nullptr){
            return new Node(word,meaning );
        }


        if(word < root->word){
            root->left= insert(root->left, word, meaning);
        }


        else if(word > root->word){
            root->right= insert(root->right,word,meaning);
        }


        return root;
    }


    Node* search(Node* root , string word, bool& found){
        if(root==nullptr){
            return nullptr;
        }


        if(root->word== word){
            found=true;
            return root;
        }


        if(word< root->word){
            return search(root->left,word,found);


        }else{
            return search(root->right,word,found);
        }
    }


    Node* findMin(Node* root){
        while(root!=nullptr && root->left != nullptr){
            root=root->left;
        }


        return root;
    }
    Node* remove(Node* root, string word){
        if(root== nullptr){
            return nullptr;
        }


        if(word< root->word){
            root->left=remove(root->left,word);
        }else if(word > root -> word){
            root ->right =remove (root->right, word);




    }else{
        if(root->left==nullptr){
            Node* temp=root->right;
            delete root;
            return temp;
        }else if(root->right == nullptr){
            Node* temp=root ->left;
            delete root;
            return temp;
        }


        Node* temp = findMin(root->right);
        root->word=temp->word;
        root->meaning= temp-> meaning;


        root->right= remove (root->right, temp->word);


    }


    return root;
    }


   void suggestWords(Node* root, const string& matchText, SuggestionNode*& head, bool isPrefix) {
    if (root == nullptr) return;


    if (isPrefix) {
        if (root->word.substr(0, matchText.length()) == matchText) {
            SuggestionNode* newNode = new SuggestionNode(root->word);
            newNode->next = head;
            head = newNode;
        }
    } else {
        if (root->word.length() >= matchText.length()) {
            if (root->word.substr(root->word.length() - matchText.length()) == matchText) {
                SuggestionNode* newNode = new SuggestionNode(root->word);
                newNode->next = head;
                head = newNode;
            }
        }
    }


    suggestWords(root->left, matchText, head, isPrefix);
    suggestWords(root->right, matchText, head, isPrefix);
}




    void inorder(Node* root){
        if(root==nullptr)
            return;


        inorder(root->left);
        cout<< root->word<< ":"<< root->meaning <<endl;
        inorder(root->right);
    }




public:
    Dictionary(){
        root=nullptr;
    }


    void insert(const string& word ,const string& meaning){
        root = insert(root,word,meaning);
    }




    void remove(const string& word){
        root=remove(root,word) ;


         }


    void search(const string& word)  {
        bool found =false;
        Node* result = search(root, word, found);




        if(found){
            cout<< word << ": "<< result->meaning << endl;
        }else{


            cout << "The word \"" << word << "\" was not found." << endl;


            SuggestionNode* suggestions= nullptr;


            if(word.length() >= 3) {
    string prefix = word.substr(0, 3);
    suggestWords(root, prefix, suggestions, true);  // true means prefix-based
}


if(suggestions == nullptr && word.length() >= 3) {
    string postfix = word.substr(word.length() - 3);
    suggestWords(root, postfix, suggestions, false);  // false means postfix-based
}




            if(suggestions != nullptr){
                cout<< "Did you mean: ";
                SuggestionNode* current=suggestions;
                bool first=true;
                while(current !=nullptr){
                    if(!first){
                        cout<< ", ";
                    }
                    cout << "\"" << current->word << "\"";
                    first= false;
                    current =current->next;


                }


                cout << "?"<< endl;


                //free memory


                while(suggestions != nullptr){
                    SuggestionNode* temp=suggestions;
                    suggestions=suggestions->next;
                    delete temp;
                }




            }else{
                cout << "No suggestions found." << endl;
            }


        }
    }


    void display() {
        inorder(root);
    }


    void loadFromFile(string filename){
        ifstream file(filename.c_str());
        if(!file){
            cout<< "File not found!\n";
            return;
        }


        string word,meaning;
        while(file>> word){
            getline (file, meaning );


            if(!meaning.empty() && meaning[0]==' ')meaning =meaning.substr(1);
            insert(word,meaning);


        }
        file.close();
    }




};






int main(){


    Dictionary dict;
    dict.loadFromFile("C:\\Users\\Asus\\Downloads\\dictIonary word.txt");


    int choice;
    string word,meaning;


    while(true){
        cout << "\nDictionary Menu\n";
        cout<< "1. Add Word\n";
        cout<< "2.Search Word\n";
        cout<< "3.Delete Word\n";
        cout<< "4.Display All Words\n";
        cout<< "5. Exit\n";
        cout<< "Enter the choice: ";


        cin>> choice;
        cin.ignore();


        switch(choice){
        case 1:
            cout<< "Enter the Word: ";
            getline(cin,word);
            cout<< "Enter meaning: ";
            getline(cin,meaning);
            dict.insert(word,meaning);
            break;


        case 2:
            cout<< "Enter word to search: ";
            getline(cin,word);
            dict.search(word);
            break;


        case 3:
            cout << "Enter word to delete: ";
            getline(cin,word);
            dict.remove(word);
            break;


        case 4:
            dict.display();
            break;


        case 5:
            cout<< "Exiting ...\n";
            return 0;


        default:
            cout<< "Invalid choice!\n";






        }




    }


}
