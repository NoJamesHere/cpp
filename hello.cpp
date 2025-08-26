#include <iostream>
#include <limits>
// Adding numbers together
int add(int a, int b){
    return a + b;
}

int sub(int a, int b){
    return a - b;
}

// Function for checking if the number are the same
bool same(int a, int b){
    return a == b;
}

int mult(int a, int b){
    return a * b;
}

float divide(int a, int b){
    return static_cast<float>(a) / b;
}

int remainder(int a, int b){
    return a % b;
}

// main function

int main() {
    bool result1;
    bool result;

    int num1;
    int num2;
    // The input stays in the same line because a newline character ("\n") 
    // was not entered at the end of the character output ("std::cout")
    std::cout << "Enter your first number: ";
    if (!(std::cin >> num1)){
        std::cout << "Bruh that's not a fuckin' number 💀\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 1;
    }
    std::cout << "\nEnter your second number: ";
    if (!(std::cin >> num2)) {
        std::cout << "Bruh that's not a fuckin' number 💀\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 1;
    }
    
    int added = add(num1,num2);
    std::cout << "Your input " << num1 << " added with " << num2 << " results in: " << added << "\n";

    int subb = sub(num1, num2);
    std::cout << "Your input " << num1 << " subtracted by " << num2 << " results in: " << subb << "\n";
    
    int multi = mult(num1, num2);
    std::cout << "Your input " << num1 << " multiplied with " << num2 << " results in: " << multi << "\n";

    float divided = divide(num1, num2);
    std::cout << "Your input " << num1 << " divided through " << num2 << " results in: " << divided << "\n";
    
    float remain = remainder(num1,num2);
    std::cout << "Your input " << num1 << " of the remainder " << num2 << " results in: " << remain << "\n";
   

    result1 = same(num1,num2);
    std::cout << "\nYour input " << num1 << " and " << num2 << " are ";
    if(result1){
        std::cout << "the same." << "\n";
    }
    else{
        std::cout << "not the same." << "\n";
    }

    std::cout << "\n\nInterpreter:\n";
    return 0;
}
