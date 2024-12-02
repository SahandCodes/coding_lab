# include<iostream>
# include<optional>

int Add(const int &x, const int &y){
    return x + y;
}

std::optional<int> Add(const int *x, const int *y){
    if (x == nullptr || y == nullptr) {
        return std::nullopt;
    }
    return *x + *y;
}

int main(){
    int a{2};
    int b{3};
    int *PtrA = &a;
    int *PtrB = &b;
    int sum = Add(a, b);
    std::cout<<a<<" + "<<b<<" = "<<sum<<std::endl;
    
    *PtrA = *PtrA + 1;
    auto sum2 = Add(PtrA, PtrB);
    if (sum2.has_value()){
        std::cout<<*PtrA<<" + "<<*PtrB<<" = "<<sum2.value()<<std::endl;
    } else{
        std::cout<<"Error: One or both of the pointers are null";
    }
   
    PtrA = nullptr;
    sum2 = Add(PtrA, PtrB);
    if (sum2.has_value()){
        std::cout<<*PtrA<<" + "<<*PtrB<<" = "<<sum2.value()<<std::endl;
    } else{
        std::cout<<"Error: One or both of the pointers are null"<<std::endl;
    }
    return 0;
}

