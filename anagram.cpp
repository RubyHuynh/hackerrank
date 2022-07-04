#include<iostream>
#include<ostream>


int anagram(std::string s) {
    int rs = 0;
    int j;
    int pos = s.size()/2;

    std::cout << __func__ << " str=" << s << " pos=" << pos;

    if (!pos&1) return -1;
    
    pos -= 1;
    
    for (int i = 0; i <= pos; i++) {
        for (j = pos + 1; j < s.size(); j++) {
            if (s[i] == s[j]) break;            
        }
        if (j == s.size()) rs++;
    }
    return rs;
}

int main() {
	std::cout << "\n\t rs = " << anagram(std::string("abcdef"));
	std::cout << "\n";
}
