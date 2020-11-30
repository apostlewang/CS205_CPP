#include<iostream>
#include<string>
#include<stack>
#include<queue>
using namespace std;
bool num(char c){
    if(c >= '0'&& c <= '9'){
        return true;
    }
    return false;
}

bool isNumber(string s){
    if(s=="+"||s=="-"||s=="*"||s=="/"){
        return false;
    }
    return true;
}

string calculate(string a, string b, string op){
    //用于计算a op b 
    //将字符串转为double
    double x = atof(a.c_str());
    double y = atof(b.c_str());
    if(op=="+"){
        return to_string(x+y);
    }
    else if(op=="-"){
        return to_string(x-y);
    }else if(op=="*"){
        return to_string(x*y);
    }else if(op=="/"){
        return to_string(x/y);
    }

}

int main(){
    //辅助将中缀表达式转为后缀表达式的栈
    stack<char>symbolStack;
    //队列q用于存储后缀表达式
    queue<string>q;
    cout << "欢迎使用计算器,输入Exit退出" << endl;
    
    while (1)
    {
        string exp;
        cin >> exp;
        if(exp == "Exit"){
            break;
        }
        int i = 0;
        int size = exp.size();
        //遍历用户输入，将前缀表达式转化为后缀表达式
        while(i<size){
            char c = exp[i];
            i++;
            string b(1,c);
            if(num(c)){
                if(!num(exp[i])&&exp[i]!='.'){
                    //如果是一位数的数字，直接放入队列
                    q.push(b);
                }
                else{
                    string d(1,exp[i]);
                    string temp =b+d;
                    //如果遇到连续的数字
                    i++;
                    if(i<size){
                        while(num(exp[i])||exp[i]=='.'){
                            string f(1,exp[i]);
                            temp+=f;
                            i++;
                            if(i==size){
                                break;
                            }
                        }
                    }                  
                    q.push(temp);
                }
                
                
            }
            else if(c == '+'||c == '-'){
                //对于+-两种优先级最低的符号，符号栈一直需要pop元素到队列直到栈为空或者遇到左括号
                while(!symbolStack.empty()&&symbolStack.top()!='('){
                    string a(1,symbolStack.top());
                    q.push(a);
                    symbolStack.pop();
                }
                //符号入栈
                symbolStack.push(c);
            }
            
            else if(c == '*'||c == '/'){
                //对于*/两种高优先级符号，只有栈顶为*或者/的时候需要pop元素到队列
                while(!symbolStack.empty()&&symbolStack.top()!='('&&
                symbolStack.top()!='+'&&symbolStack.top()!='-'){
                    string a(1,symbolStack.top());
                    q.push(a);
                    symbolStack.pop();
                }
                //符号入栈
                symbolStack.push(c);
            }
            else if(c == '('){
                //左括号直接入栈
                symbolStack.push(c);
                
            }
            else if(c ==')'){
                //遇到右括号会一直pop栈中的元素到队列直到左括号在栈顶
                while(symbolStack.top()!='('){
                    string p (1,symbolStack.top());
                    symbolStack.pop();
                    q.push(p);
                }
                //pop出左括号（不加入队列）
                symbolStack.pop();
            }

        }
        //如果符号栈中还有元素，依次pop出到队列中
        while(!symbolStack.empty()){
            string p (1,symbolStack.top());
            q.push(p);
            symbolStack.pop();
        }
        //执行完后已经得到后缀表达式在队列q中

        //需要一个新的辅助栈来求值
        stack<string> cal;
        while(!q.empty()){
            //遍历后缀表达式队列中的所有元素
            //Excout<<q.front()<<endl;
            if(isNumber(q.front())){
                //遇见数字时入栈
                cal.push(q.front());           
            }
            else{
                //遇见操作符，出栈2个数字b,a做a op b运算
                string b = cal.top();
                cal.pop();
                string a = cal.top();                
                cal.pop();
                string result = calculate(a,b,q.front());
                cal.push(result);              
            }
            q.pop();
        } 
        //最后留在栈中的元素即为运算结果
        string result = cal.top();
        cout<<result<<endl;    
        
    }
    return 0;

}