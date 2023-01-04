#include<iostream>
#include<stack>
#include<deque>

bool isImpossible(char close_value, char open_value)
{
    if((close_value == '}') && (open_value != '{'))
        return true;
    
    if((close_value == ']') && (open_value != '['))
        return true;

    if((close_value == ')') && (open_value != '('))
        return true;

    return false;
}

void solution()
{
    std::string input_str;
    std::cin >> input_str;

    std::stack<char> open_st;
    std::deque<char> deq;

    for(auto tmp : input_str)
    {
        if((tmp == '{') || (tmp == '[') || (tmp == '('))
        {
            open_st.push(tmp);
            deq.push_back(tmp);
        }
        else
        {
            if(open_st.empty())
            {
                if(tmp == '}')
                    deq.push_front('{');
                else if(tmp == ']')
                    deq.push_front('[');
                else
                    deq.push_front('(');
            }
            else
            {
                if(isImpossible(tmp, open_st.top()))
                {
                    std::cout << "IMPOSSIBLE";
                    return;
                }
                open_st.pop();
            }
            deq.push_back(tmp);
        }
    }

    while (!open_st.empty())
    {
        auto tmp = open_st.top();

        if(tmp == '{')
            deq.push_back('}');
        else if(tmp == '[')
            deq.push_back(']');
        else
            deq.push_back(')');

        open_st.pop();
    }

    for(auto tmp : deq)
        std::cout << tmp;
        
    std::cout << std::endl;
}

int main()
{
    solution();
    return EXIT_SUCCESS;
}