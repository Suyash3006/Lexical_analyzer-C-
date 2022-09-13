#include<iostream>
#include<vector>
#include<iterator>
#include<map>
#include<unordered_map>
#include<fstream>
#include<cstring>
#include "def.h"
#include "keyword_gen.h"

using namespace std;


unordered_map<string , int> token_check; // in order to check  the maintainence of the symbol table
// what is needed to be updated 

// identifier check function is for checking the whether the token is identifier or keyword for
// symbol table updation 
bool identifier_check(string value){
    int size = value.size();
    if(value[0] == '_' || (value[0] >= 'a' && value[0] <= 'z') || (value[0] >= 'A' && value[0] <= 'Z')){
        return true;    
    }
    return false;
}

// this function identifies whehter the token is identifier or keyword of the P language
string type_find(string val){
    string keyword_name;
    if(val == "int" || val == "short" || val == "float" || val == "double" || val == "bool" ||
    val == "char" || val == "signed" || val == "unsigned" || val == "for" || val == "while" ||
    val == "do" || val == "return" || val == "void" || val == "switch" || val == "break" ||
    val == "case" || val == "continue" || val == "goto" || val == "long" || val == "static" ||
    val == "union" || val == "default" || val == "main"){
        keyword_name = "Keyword";
    }else{
        keyword_name = "Identifier";
    }
    return keyword_name;
}

// this is function used for checking whether symbol table files already contains the token 
// or not  so that updation of symbol table can be made line by line of the code.
bool check_in_symbolTable(string symbol){
    if(token_check[symbol] == 0){
        return false;
    }else{
        return true;
    }
    FILE* symbol_table;
    symbol_table = fopen("symbol_table_1.out" , "r");
    char str[1001];
    while(fgets(str , 1001 , symbol_table) != NULL){
        string sub = str;
        int i=0;
        while(sub[i] != '\t'){
            i++;
        }
        sub = sub.substr(0,i);
        if(sub == symbol){
            return true;
        }    
    }
    return false;
}
 
// this function species the token Id of the token in the given input.in file so that
// pa_1.out file could be updated accordingly
int get_tokenID(string token_){
    string ans;
    int id;
    if((token_[0] == '_') || (token_[0] >= 'a' && token_[0] <= 'z') || (token_[0] >= 'A' && 
    token_[0] <= 'Z')){
        ans = type_find(token_);
        if(ans == "Identifier"){
            id = IDNTIFIER;
        }else{
            id = keyword_find(token_);
        }
    }else if(token_[0] >= '0' && token_[0] <= '9'){
        ans = "int_const";
        id = INT_CONST;
        bool flag = false;
        for(int i=0;i<token_.size();i++){
            if(token_[i] == '.'){
                flag = true; 
                break;
            }
        }
        if(flag){
            ans = "flo_const";
            id  = FLO_CONST;
        }
    }else{
        id = keyword_find(token_);
    }
    return id;
}
 
// this function is for the updation of the pa_1 file using pointers at the end of file &&
// file is opened in append mode in order to prevent overwrite of the content and append 
// the given content or token to be updated.
void updatePa_1(map<string,int> &token_map){
    FILE* tokenFile;
    tokenFile = fopen("pa_1.out" , "a+");
    if(tokenFile == NULL){
        cout<<"Not able to create a File"<<endl;
    }else{
        map<string,int> :: iterator TokenIT = token_map.begin();
        while(TokenIT != token_map.end()){
            int Tid = get_tokenID(TokenIT -> first);
            char tem[1001] , te[1001];
            sprintf(tem , "%d" , Tid);
            strcpy(te , TokenIT->first.c_str());
            fputs(tem , tokenFile);
            fputs("\t" , tokenFile);
            fputs(te , tokenFile);
            fputs("\n" , tokenFile);
            TokenIT++;
        }
        fclose(tokenFile);
    }    
}


// This is basically for the purpose of updating the symbol_table.out file in the context of new
// tokens in the upcoming lines of the code in such a way that repeated tokens should be addressed 
// and prevented from getting redundant in the output file.
void append_tokens(map<string,int> &token_map){
    FILE* outputfile;
    outputfile = fopen("symbol_table_1.out" ,"a+");
    if(outputfile == NULL){
        cout<<"symbol table file not created"<<endl;
    }else{
        // cout<<"symbol_table created"<<endl;
        char arr_str[1001];
        map<string,int> :: iterator dict_it = token_map.begin();
        while(dict_it != token_map.end()){
            if(check_in_symbolTable(dict_it->first) == false && identifier_check(dict_it -> first)){
                string lexeme_type = type_find(dict_it-> first);
                char helper[1001];
                strcpy(helper , lexeme_type.c_str());
                strcpy(arr_str , dict_it->first.c_str());
                fputs( arr_str, outputfile);
                fputs("\t"  , outputfile);
                fputs(helper , outputfile);
                fputs("\n" , outputfile);
                token_check[dict_it->first] = 1;
            }
            dict_it ++ ;
        }
    }
}

// fucntion get_tokens is used for the purpose of counting the tokens in the token_map;
int get_tokens(map<string,int> &token_map){
    int size_token = token_map.size();
    map<string,int> :: iterator token_ptr = token_map.begin();

    int Token_sum = 0;
    while(token_ptr != token_map.end()){
        cout<<token_ptr -> first<<" "<<token_ptr -> second<<endl;
        Token_sum += (token_ptr -> second) ;
        token_ptr++;
    }
    return Token_sum;
}

// this function converts the code of the input.in file in the string value and seperate the 
// tokens from the string value;
void tokenCounter(string linestring , map<string,int> &token_map){
    int str_size = linestring.size();   
    string sub_str = "";
    for( int i = 0 ; i < str_size ; i++ ){
        if(linestring[i] == '/' && linestring[i+1] == '*'){
            int j = i+2;
            while(j < str_size && linestring [j] == '*' && linestring[j+1] == '/'){
                j++;
            }
            i = j+1;
            continue;
        }else if(linestring[i] == '_' || (linestring[i] >= 'a' && linestring[i] <= 'z') || 
        (linestring[i] >= 'A' && linestring[i] <= 'Z') || 
        (linestring[i] >= '0' && linestring[i] <= '9')){ 
            if(!sub_str.empty() && ((sub_str[sub_str.size() - 1] >= 'a' && sub_str[sub_str.size() - 1] <= 'z') || 
            (sub_str[sub_str.size() - 1] >= 'A' && sub_str[sub_str.size() - 1] <= 'Z') || 
            (sub_str[sub_str.size() - 1] >= '0' && sub_str[sub_str.size() - 1] <= '9'))){
                sub_str += linestring[i];
            }else if(sub_str.empty()){
                sub_str += linestring[i];
            }else{
                token_map[sub_str]++;
                sub_str = "";
                sub_str += linestring[i];
            }
        }else if(linestring[i] == '\t' || linestring[i] == '\n' || linestring[i] == ' '){
            if(!sub_str.empty())
                token_map[sub_str]++;
            sub_str = "";
        }
        else{
            if(linestring[i] == '"'){
                int j = i + 1;
                while(j < str_size && linestring[j] != '"'){
                    j++;
                }
                i = j;
                continue;
            }
            if(!sub_str.empty()){
                if((sub_str[sub_str.size() - 1] == '+' && linestring[i] == '+') ||
                (sub_str[sub_str.size() - 1] == '+' && linestring[i] == '=') ||
                (sub_str[sub_str.size() - 1] == '-' && linestring[i] == '-') ||
                (sub_str[sub_str.size() - 1] == '-' && linestring[i] == '=') ||
                (sub_str[sub_str.size() - 1] == '*' && linestring[i] == '=') ||
                (sub_str[sub_str.size() - 1] == '/' && linestring[i] == '=') ||
                (sub_str[sub_str.size() - 1] == '>' && linestring[i] == '=') ||
                (sub_str[sub_str.size() - 1] == '<' && linestring[i] == '=') ||
                (sub_str[sub_str.size() - 1] == '=' && linestring[i] == '=')
                ){
                    token_map[sub_str + linestring[i]]++;
                    i++;
                }else{
                        token_map[sub_str]++;
                }
            }
            sub_str = "";
            if(i < str_size && (linestring[i] != ' ' && linestring[i] != '\t' && linestring[i] != '\n'))
                sub_str += linestring[i];
        }
    }
    if(!sub_str.empty())
        token_map[sub_str]++;
    append_tokens(token_map);
}

// 
int main(){

    // input pointer which would be pointing to the input.in file.
    FILE* inputFile;
    inputFile = fopen("input.in","r"); // "r" defines the read mode of the file in the given context

    char input_string[10000]; // input is read line by line and stored in the string named "input_string"
    

    if(inputFile == NULL){
        cout<<"Failed to read the input from input.in"<<endl;
    }else{
        //  line by line reading of the input from input.in file.
        map<string , int> token_map;
        while(fgets(input_string , 10000 , inputFile) != NULL){
            
            string lineString = input_string;

            tokenCounter(lineString,token_map);           
        }
        int token_count = get_tokens(token_map);

        updatePa_1(token_map);
        // closing the file after takin the input from the input.in file.
        cout<<"Total_Number of tokens in the input.in are : "<<token_count<<endl;
        fclose(inputFile);

        cout<<"Data is read sucessfully"<<endl;
        cout<<"File is closed now"<<endl;
    }
}