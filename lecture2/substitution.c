#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){

    // 그러니까 각 글자에 대응하는 것을 출력해내면 된다. 
    // normal -> algorithm -> encrypted
    
    if(argc==1 || argc >= 3){
        printf( "Usage : ./substitution key\n" );
    }
    else if(argc ==2){
        if(strlen(argv[1]) !=26){
            printf("Key must contain 26 characters.\n");
        }else{
            string key = argv[1];
            bool isalphabet = true;
            for(int i=0; i<26; i++){
                if( (key[i] >= 'A' && key[i] <='Z') || (key[i] >= 'a' && key[i] <='z')){
                    
                }else{
                    isalphabet = false;
                    break;
                }
            }

            // key가 alphabet을 다 포함하지 않으면, 
            // 오류 메시지를 반환한다.
            if(!isalphabet){
                printf("Keys are not a set of alphabets\n");
                return 1;
            }
            // key가 alphabet을 다 포함하면, 
            // plain을 이용해 암호화된 결과값을 반환한다.
            else{
                string plain = get_string("plain: ");
                printf("\n");
                int idx = 0;
                // plain의 각 글자를, 
                // key 값에 맞게 출력을 한다.

                // 대소문자를 구분해서 출력하고,
                // 대소문자랑 관계 없으면 그냥 출력한다.
                printf("ciphertext: ");
                while(plain[idx] != '\0'){
                    char c = plain[idx];
                    if( c >= 'A' && c<='Z' || c>='a' && c<='z'){
                        int encIdx = -1;
                        if(c>='A' && c<='Z'){
                            encIdx = c-'A';
                            printf("%c", key[encIdx]);
                        }else{
                            encIdx = c-'a';
                            printf("%c", key[encIdx] + 'a'-'A');
                        }
                    }else{
                        printf("%c", c);
                    }
                    
                    idx++;
                    
                }

                printf("\n");
            }
        }


    }


}