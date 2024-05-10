#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <ctype.h>  
  
// 函数声明  
int find_array_size(const char *str);  
void parse_and_print_array(const char *str);  
  
int main() {  
    char input[101]; // 假设输入字符串长度不超过100，包括结束符'\0'  
    fgets(input, sizeof(input), stdin); // 从标准输入读取字符串  
    // 移除字符串末尾的换行符（如果有的话）  
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
            // 假设数组长度紧跟在']'之前，并且是数字  
            size = atoi(str - 1); // 注意：这只是一个简化的处理，可能不适用于所有情况  
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
  
    // 假设输入的字符串格式相对规范，并且我们仅处理大括号内的初始化值  
    while (*str) {  
        if (*str == '{') {  
            in_init = 1;  
        } else if (*str == '}') {  
            break; // 结束初始化列表  
        } else if (in_init && isdigit(*str)) {  
            reading_value = 1;  
            value = 0;  
            sign = 1;  
            // 读取整数  
            while (reading_value && isdigit(*str)) {  
                value = value * 10 + (*str - '0');  
                str++;  
            }  
            if (str[-1] == '-') {  
                sign = -1;  
            }  
            // 处理符号（如果存在）  
            if (sign == -1) {  
                value = -value;  
            }  
            // 输出值  
            printf("%d ", value);  
            index++;  
            if (index < size) {  
                // 查找下一个逗号或结束大括号  
                while (*str && *str != ',' && *str != '}') {  
                    str++;  
                }  
                if (*str == ',') {  
                    str++; // 跳过逗号  
                }  
            }  
            reading_value = 0;  
        }  
        str++;  
    }  
  
    // 如果没有初始化值或初始化值数量少于数组长度，则输出N  
    for (; index < size; index++) {  
        printf("N ");  
    }  
    printf("\n"); // 换行  
}
