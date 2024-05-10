#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <ctype.h>  
  
// ��������  
int find_array_size(const char *str);  
void parse_and_print_array(const char *str);  
  
int main() {  
    char input[101]; // ���������ַ������Ȳ�����100������������'\0'  
    fgets(input, sizeof(input), stdin); // �ӱ�׼�����ȡ�ַ���  
    // �Ƴ��ַ���ĩβ�Ļ��з�������еĻ���  
    input[strcspn(input, "\n")] = 0;  
  
    parse_and_print_array(input);  
  
    return 0;  
}  
  
int find_array_size(const char *str) {  
    int size = 0;  
    int in_brackets = 0;  
    while (*str) {  
        if (*str == '[') {  
            in_brackets = 1;  
        } else if (in_brackets && *str == ']' && isdigit(*(str - 1))) {  
            // �������鳤�Ƚ�����']'֮ǰ������������  
            size = atoi(str - 1); // ע�⣺��ֻ��һ���򻯵Ĵ������ܲ��������������  
            break;  
        }  
        str++;  
    }  
    return size;  
}  
  
void parse_and_print_array(const char *str) {  
    int size = find_array_size(str);  
    int in_init = 0;  
    int value = 0;  
    int index = 0;  
    int sign = 1;  
    int reading_value = 0;  
  
    // ����������ַ�����ʽ��Թ淶���������ǽ�����������ڵĳ�ʼ��ֵ  
    while (*str) {  
        if (*str == '{') {  
            in_init = 1;  
        } else if (*str == '}') {  
            break; // ������ʼ���б�  
        } else if (in_init && isdigit(*str)) {  
            reading_value = 1;  
            value = 0;  
            sign = 1;  
            // ��ȡ����  
            while (reading_value && isdigit(*str)) {  
                value = value * 10 + (*str - '0');  
                str++;  
            }  
            if (str[-1] == '-') {  
                sign = -1;  
            }  
            // ������ţ�������ڣ�  
            if (sign == -1) {  
                value = -value;  
            }  
            // ���ֵ  
            printf("%d ", value);  
            index++;  
            if (index < size) {  
                // ������һ�����Ż����������  
                while (*str && *str != ',' && *str != '}') {  
                    str++;  
                }  
                if (*str == ',') {  
                    str++; // ��������  
                }  
            }  
            reading_value = 0;  
        }  
        str++;  
    }  
  
    // ���û�г�ʼ��ֵ���ʼ��ֵ�����������鳤�ȣ������N  
    for (; index < size; index++) {  
        printf("N ");  
    }  
    printf("\n"); // ����  
}
