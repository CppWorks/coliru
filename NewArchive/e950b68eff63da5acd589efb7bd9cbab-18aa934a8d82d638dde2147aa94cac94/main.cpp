#include<iostream>
using namespace std; int main(){int i=0; string ss[50]; cout<<'#'<<'i'<<'n'<<'c'<<'l'<<'u'<<'d'<<'e'<<'<'<<'i'<<'o'<<'s'<<'t'<<'r'<<'e'<<'a'<<'m'<<'>'<<endl;
ss[i++]="using namespace std; int main(){int i=0; string ss[50]; cout<<'#'<<'i'<<'n'<<'c'<<'l'<<'u'<<'d'<<'e'<<'<'<<'i'<<'o'<<'s'<<'t'<<'r'<<'e'<<'a'<<'m'<<'>'<<endl;";
for (int j=0; j<5; j++) {
ss[i++]="for (int j=0; j<5; j++) {";
cout << ss[j] << endl;
ss[i++]="cout << ss[j] << endl;";
cout << 's'<<'s'<<'['<<'i'<<'+'<<'+'<<']'<<'=' << (char)34 << ss[j] << (char)34 << ';' << endl;
ss[i++]="cout << 's'<<'s'<<'['<<'i'<<'+'<<'+'<<']'<<'=' << (char)34 << ss[j] << (char)34 << ';' << endl;";
if(j==4) cout << '}' << '}'<<endl;
ss[i++]="if(j==4) cout << '}' << '}'<<endl;";
}}