#include "bignumber.h"
#include <iostream>
#include <cstdlib>
#include "handyfunctions.h"

using namespace std;

BigNumber::BigNumber(){
    for(int i = 0; i < 200; i++){
        this->number[i] = 0;
    }
    start = 100;
    end = 100;
    negative = false;
}

BigNumber::BigNumber(string input){
    for(int i = 0; i < 200; i++){
        this->number[i] = 0;
    }

    string str;
    if(input.substr(0,1) == "-"){
        negative = true;
        str = input.substr(1);
    }else{
        negative = false;
        str = input;
    }
    vector<string> v = split(str, ".");

    if(v.size() == 1){
        string num = v.at(0);
        int len = num.length();
        // let index 100 be the one's digit
        int index = 0;
        start = 100+len-1;
        end = 100;
        for(int i = 100 + len-1; i >= 100; i--){
            number[i] = stoi(num.substr(index, 1));
            index++;
        }
    }

    if(v.size() == 2){
        string num = v.at(0);
        int len = num.length();
        // let index 100 be the one's digit
        int index = 0;
        start = 100 + len-1;
        for(int i = 100 + len-1; i >= 100; i--){
            number[i] = stoi(num.substr(index, 1));
            index++;
        }

        string num2 = v.at(1);
        int len2 = num2.length();
        //0~99 are decimal numbers
        int index2 = 0;
        for(int i = 99; i > 99-len2; i--){
            number[i] = stoi(num2.substr(index2, 1));
            index2++;
        }
        end = 99-len2+1;
    }

}

BigNumber::BigNumber(const BigNumber &other){
    for(int i = 0; i < 200; i++){
        this->number[i] = other.number[i];
    }
    this->start = other.start;
    this->end = other.end;
    this->negative = other.negative;
}

BigNumber& BigNumber::operator =(const BigNumber& right){
    for(int i = 0; i < 200; i++){
        this->number[i] = right.number[i];
    }
    this->start = right.start;
    this->end = right.end;
    this->negative = right.negative;
    return *this;
}

void BigNumber::print(){
    for(int i = 199; i >= 0; i--){
        cout<<i<<"\t"<<this->number[i]<<endl;
    }
}

void BigNumber::printnumber(){
    for(int i = start; i >= end; i--){
        cout<<number[i];
        if(i == 100){
            cout<<".";
        }
    }
    cout<<endl;
}

string BigNumber::getValue(){
    string output = "";
    int startingPoint = 0;
    for(int i = start; i >= end; i--){
        if(number[i] != 0){
            startingPoint = i;
            break;
        }
    }
    for(int i = startingPoint; i >= end; i--){
        output+=to_string(number[i]);
    }
    return output;
}

int BigNumber::getLength(){
    return getValue().length();
}

BigNumber BigNumber::operator +(BigNumber right){
    BigNumber output("0");

    //if both numbers are positive or negative
    if((!this->negative && !right.negative) || (this->negative && right.negative)){
        //define the highest digit among the two inputs
        int a;
        if(this->end < right.end){
            a=this->end;
        }else{
            a=right.end;
        }

        //define the lower bound of the two inputss
        int b;
        if(this->start > right.start){
            b = this->start;
        }else{
            b = right.start;
        }

        for(int i = a; i <= b; i++){
            int increment;
            int sum = output.number[i]+this->number[i]+right.number[i];
            int digit = sum%10;
            increment = sum/10;
            output.number[i]= digit;
            output.number[i+1] += increment;
            //output.printnumber();
            if(i+1 > b && output.number[i+1] != 0){
                output.start=i+1;
            }else{
                output.start = i;
            }
        }
        output.end = a;
        if(this->negative){
            output.negative = true;
        }else{
            output.negative = false;
        }

        return output;
    }
    //if left is negative and right is positive
    else if(this->negative && !right.negative){
        //perform right-left
        BigNumber* templeft = new BigNumber(*this);
        BigNumber* tempright = new BigNumber(right);
        templeft->negative = false;
        tempright->negative = false;
        output = *tempright-*templeft;

        delete templeft;
        delete tempright;
    }
    //if left is positive and right is negative
    else{
        //perform left-right
        BigNumber* templeft = new BigNumber(*this);
        BigNumber* tempright = new BigNumber(right);
        templeft->negative = false;
        tempright->negative = false;
        output = *templeft-*tempright;

        delete templeft;
        delete tempright;
    }
    return output;
}

BigNumber BigNumber::operator -(BigNumber right){
    BigNumber output;
    if(*this == right){
        output.start = 100;
        output.end = 100;
        output.negative = false;
        return output;
    }
    output.start = 100;
    output.end = 100;

    //if both are positive and left > right
    if((!this->negative && !right.negative)&&*this>right){                     //if both are positive and left > right
        for(int i = 0; i < 200; i++){
            int difference = output.number[i] + this->number[i]-right.number[i];
            int digit;
            int increment;
            if(difference >= 0){
                digit = difference;
                increment = 0;
            }else{
                digit = 10+difference;
                increment = -1;
            }
            output.number[i] = digit;
            output.number[i+1] += increment;
        }
        output.negative = false;
    }else if((!this->negative && !right.negative)&& *this<right){              //if both are positive and left < right
        for(int i = 0; i < 200; i++){
            int difference = output.number[i] + right.number[i]-this->number[i];
            int digit;
            int increment;
            if(difference >= 0){
                digit = difference;
                increment = 0;
            }else{
                digit = 10+difference;
                increment = -1;
            }
            output.number[i] = digit;
            output.number[i+1] += increment;
        }
        output.negative = true;

    }else if((this->negative && right.negative)&& *this > right){              //if both are negative && left > right
        for(int i = 0; i < 200; i++){                                                       //basically, calculation will be right-left and make it positive
            int difference = output.number[i] + right.number[i] -this->number[i];
            int digit;
            int increment;
            if(difference >= 0){
                digit = difference;
                increment = 0;
            }else{
                digit = 10+difference;
                increment = -1;
            }
            output.number[i] = digit;
            output.number[i+1] += increment;
        }
        output.negative = false;

    }else if((this->negative && right.negative)&& *this < right){              //when both are negative and left < right
        for(int i = 0; i < 200; i++){                                                       //basically, calculation will be left-right and make it negative
            int difference = output.number[i] + this->number[i] - right.number[i];
            int digit;
            int increment;
            if(difference >= 0){
                digit = difference;
                increment = 0;
            }else{
                digit = 10+difference;
                increment = -1;
            }
            output.number[i] = digit;
            output.number[i+1] += increment;
        }
        output.negative = true;

    }else if(this->negative && !right.negative){                               //when left < 0, right > 0
                                                                                            //basically, left+right and make it negative
        //define the highest digit among the two inputs
        int a;
        if(this->end < right.end){
            a=this->end;
        }else{
            a=right.end;
        }

        //define the lower bound of the two inputss
        int b;
        if(this->start > right.start){
            b = this->start;
        }else{
            b = right.start;
        }

        for(int i = a; i <= b; i++){
            int increment;
            int sum = output.number[i]+this->number[i]+right.number[i];
            int digit = sum%10;
            increment = sum/10;
            output.number[i]= digit;
            output.number[i+1] += increment;
            //output.printnumber();
            if(i+1 > b && output.number[i+1] != 0){
                output.start=i+1;
            }else{
                output.start = i;
            }
        }
        output.end = a;
        output.negative = true;

    }else{
        //define the highest digit among the two inputs
        int a;
        if(this->end < right.end){
            a=this->end;
        }else{
            a=right.end;
        }

        //define the lower bound of the two inputss
        int b;
        if(this->start > right.start){
            b = this->start;
        }else{
            b = right.start;
        }

        for(int i = a; i <= b; i++){
            int increment;
            int sum = output.number[i]+this->number[i]+right.number[i];
            int digit = sum%10;
            increment = sum/10;
            output.number[i]= digit;
            output.number[i+1] += increment;
            if(i+1 > b && output.number[i+1] != 0){
                output.start=i+1;
            }else{
                output.start = i;
            }
        }
        output.end = a;
        output.negative = false;
    }

    for(int i = 199; i >=100; i--){
        if(output.number[i] != 0){
            output.start = i;
            break;
        }
    }
    for(int i = 0; i < 100; i++){
        if(output.number[i] != 0){
            output.end = i;
            break;
        }
    }
    return output;
}

BigNumber BigNumber::operator *(BigNumber right){
    BigNumber output;

    BigNumber* shorter;
    BigNumber* longer;
    //find the number with less digits
    if(this->start-this->end > right.start-right.end){
        shorter = &right;
        longer = this;
    }else{
        shorter = this;
        longer = &right;
    }

    vector<int> wholeNumbers;   //multiplier is wholeNumbers.size()-i-1 where i starts from zero
    vector<int> decimalNumbers; //multiplier is 0.1 * (100-end+i) where i starts from zero

    for(int i = shorter->start; i >= 100; i--){
        //cout<<shorter->number[i]<<endl;
        wholeNumbers.push_back(shorter->number[i]);
    }

    for(int i = shorter->end; i < 100; i++){
        decimalNumbers.push_back(shorter->number[i]);
    }



    //here we perform multiplication with each little number we got
    //to shift the number, we are gonna change the index for the pending numbers a little
    //  bit to avoid shifting numbers later on

    for(int i = 0; i < wholeNumbers.size(); i++){
        BigNumber* temp = new BigNumber();
        int num = wholeNumbers.at(i);
        int shift = wholeNumbers.size()-i-1;

        for(int j = longer->end; j <= longer->start; j++){

            int increment;
            int product = temp->number[j+shift] + (longer->number[j] * num);
            int digit = product%10;
            increment = product/10;

            temp->number[j+shift]= digit;
            temp->number[j+1+shift] += increment;

            if(j+1+shift >= 199){
                cout<<"overflowerror"<<endl;
                exit(1);
            }
        }

        //start and end for temp
        for(int j = 199; j >= 100; j--){
            if(temp->number[j] != 0){
                temp->start = j;
                break;
            }
        }
        for(int j = 0; j <= 99; j++){
            if(temp->number[j] != 0){
                temp->end = j;
                break;
            }
        }


        output = output+*temp;
        delete temp;
    }

    for(int i = decimalNumbers.size()-1; i >= 0; i--){
        BigNumber* temp = new BigNumber();
        int num = decimalNumbers.at(i);
        int shift = i-decimalNumbers.size();  
        //cout<<num<<"\t"<<shift<<endl;
        for(int j = longer->end; j <= longer->start; j++){
            int increment;
            int product = temp->number[j+shift] + (longer->number[j] * num);
            int digit = product%10;
            increment = product/10;
            temp->number[j+shift]= digit;

            temp->number[j+1+shift] += increment;
            if(j+1+shift >= 199){
                cout<<"overflowerror"<<endl;
                exit(1);
            }
        }
        for(int j = 0; j < 100; j++){
            if(temp->number[j] != 0){
                temp->end = j;
                break;
            }
        }

        //start and end for temp
        for(int j = 199; j >= 100; j--){
            if(temp->number[j] != 0){
                temp->start = j;
                break;
            }
        }
        for(int j = 0; j <= 99; j++){
            if(temp->number[j] != 0){
                temp->end = j;
            }
            break;
        }

        output = output + *temp;
        delete temp;
    }


    // start and end for output
    for(int i = 199; i >= 100; i--){
        if(output.number[i] != 0){
            output.start = i;
            break;
        }
    }
    for(int i = 0; i <= 99; i++){
        if(output.number[i] != 0){
            output.end = i;
            break;
        }
    }

    if(this->negative == right.negative){
        output.negative = false;
    }else{
        output.negative = true;
    }

    return output;
}

BigNumber BigNumber::operator /(BigNumber right){
    int power1 = this->firstNonZero()-100;
    int power2 = right.firstNonZero()-100;
    int target = power1-power2+100;
    //cout<<target<<endl;
    BigNumber answer;
    BigNumber zero;
    int numDigitRight = 0;

    //define sign for answer
    if(this->negative == right.negative){
        answer.negative = false;
    }else{
        answer.negative = true;
    }

    //find the # of numbers in right
    for(int i = right.start; i >= right.end; i--){
        if(right.number[i] != 0){
            numDigitRight = i-right.end+1;
            break;
        }
    }

    int current = power1+100;

    string numeratorStr = this->getValue();
    string denominatorStr = right.getValue();

    BigNumber denominator(denominatorStr);

    //cout<<"numerator string "<<numeratorStr<<endl;

    string segment = numeratorStr.substr(0,numDigitRight);
    current= current-numDigitRight+1;

    while(current > 0 && target >= 0){
        BigNumber* smallTerm = new BigNumber(segment);

        while(*smallTerm < denominator){
            segment += to_string(this->number[current-1]);
            current--;

            delete smallTerm;
            smallTerm = new BigNumber(segment);
            target--;
        }
        //cout<<"numerator: "<<*smallTerm<<" "<<"denominator: "<<denominator<<endl;
        int ansdigit = 0;
        while(*smallTerm >= denominator){
            ansdigit++;
            *smallTerm = *smallTerm-denominator;
            //cout<<"\t"<<*smallTerm<<endl;
        }
        //cout<<(*smallTerm>=denominator)<<endl;

        answer.number[target]=ansdigit;
        target--;

        if(*smallTerm == zero){
            while(target>=0 && this->number[current-1] == 0){
                answer.number[target] = 0;
                target--;
                current--;
            }
        }
        if(target==0 || current == 0){
            break;
        }

        segment = smallTerm->getValue()+to_string(this->number[current-1]);
        current--;
    }

    //define start and end for answer
    for(int i = 199; i >= 100; i--){
        if(answer.number[i] != 0){
            answer.start = i;
            break;
        }
    }
    for(int i = 0; i <= 99; i++){
        if(answer.number[i] != 0){
            answer.end = i;
            break;
        }
    }
    return answer;
}





bool BigNumber::operator ==(const BigNumber& right){
    if((this->negative != right.negative) || (this->start != right.start)||(this->start != right.start)){
        return false;
    }else{      //same sign same length
        for(int i = this->start; i >= this->end; i--){
            if(this->number[i] != right.number[i]){
                return false;
            }
        }
        return true;
    }
}




bool BigNumber::operator <(const BigNumber& right){
    if(this->negative && !right.negative){          //if left is negative and right is positive
        return true;  
    }else if(!this->negative && right.negative){    //if only right is negative
        return false;
    }else if(!this->negative && !right.negative){   //if both are positive
        if(this->start < right.start){
            return true;
        }else if(this->start > right.start){
            return false;
        }else{
            int counter = 0;
            for(int i = this->start; i >= 0; i--){
                if(this->number[i] == right.number[i]){
                    counter++;
                }else if(this->number[i] < right.number[i]){
                    return true;
                }else{
                    return false;
                }
            }
            if(counter == this->start+1){
                return false;
            }
            return true;
        }
    }else{                                    //if both are negative
        if(this->start < right.start){
            return false;
        }else if(this->start > right.start){
            return true;
        }else{
            int counter = 0;
            for(int i = this->start; i >= 0; i--){
                if(this->number[i] == right.number[i]){
                    counter++;
                }else if(this->number[i] > right.number[i]){
                    return true;
                }else{
                    return false;
                }
            }
            if(counter = this->start+1){
                return false;
            }
            return false;
        }
    }
}

bool BigNumber::operator <=(const BigNumber& right){
    if(this->negative && !right.negative){          //if left is negative and right is positive
        return true;
    }else if(!this->negative && right.negative){    //if only right is negative
        return false;
    }else if(!this->negative && !right.negative){   //if both are positive
        if(this->start < right.start){
            return true;
        }else if(this->start > right.start){
            return false;
        }else{
            int counter = 0;
            for(int i = this->start; i >= 0; i--){
                if(this->number[i] == right.number[i]){
                    counter++;
                }else if(this->number[i] < right.number[i]){
                    return true;
                }else{
                    return false;
                }
            }
            if(counter == this->start+1){
                return true;
            }
            return false;
        }
    }else{                                    //if both are negative
        if(this->start < right.start){
            return false;
        }else if(this->start > right.start){
            return true;
        }else{
            int counter = 0;
            for(int i = this->start; i >= 0; i--){
                if(this->number[i] == right.number[i]){
                    counter++;
                }else if(this->number[i] > right.number[i]){
                    return true;
                }else{
                    return false;
                }
            }
            if(counter == this->start+1){
                return true;
            }
            return false;
        }
    }
}

// copied everything from operator < and flipped every true and false
bool BigNumber::operator >(const BigNumber& right){
    if(this->negative && !right.negative){          //if left is negative and right is positive
        return false;
    }else if(!this->negative && right.negative){    //if only right is negative
        return true;
    }else if(!this->negative && !right.negative){   //if both are positive
        if(this->start < right.start){
            return false;
        }else if(this->start > right.start){
            return true;
        }else{
            int counter = 0;
            for(int i = this->start; i >= 0; i--){
                if(this->number[i] == right.number[i]){
                    counter++;
                }else if(this->number[i] > right.number[i]){
                    return true;
                }else{
                    return false;
                }
            }
            if(counter == this->start+1){
                return false;
            }
            return true;
        }
    }else{  //if both are negative
        if(this->start < right.start){
            return true;
        }else if(this->start > right.start){
            return false;
        }else{      
            int counter = 0;
            for(int i = this->start; i >= 0; i--){
                if(this->number[i] == right.number[i]){
                    counter++;
                }else if(this->number[i] > right.number[i]){
                    return false;
                }else{
                    return true;
                }
            }
            if(counter == this->start+1){
                return false;
            }
            return true;
        }
    }
}

bool BigNumber::operator >=(const BigNumber& right){
    if(this->negative && !right.negative){          //if left is negative and right is positive
        return false;
    }else if(!this->negative && right.negative){    //if only right is negative
        return true;
    }else if(!this->negative && !right.negative){   //if both are positive
        if(this->start < right.start){
            return false;
        }else if(this->start > right.start){
            return true;
        }else{
            int counter = 0;
            for(int i = this->start; i >= 0; i--){
                if(this->number[i] == right.number[i]){
                    counter++;
                }else if(this->number[i] > right.number[i]){
                    return true;
                }else{
                    return false;
                }
            }
            if(counter == this->start+1){
                return true;
            }
            return false;
        }
    }else{  //if both are negative
        if(this->start < right.start){
            return true;
        }else if(this->start > right.start){
            return false;
        }else{
            int counter = 0;
            for(int i = this->start; i >= 0; i--){
                if(this->number[i] == right.number[i]){
                    counter++;
                }else if(this->number[i] > right.number[i]){
                    return false;
                }else{
                    return true;
                }
            }
            if(counter == this->start-this->end+1){
                return true;
            }
            return true;
        }
    }

}



std::ostream& operator << (std::ostream& os, const BigNumber& num){
    string out = "";
    if(num.negative == true){
        out+="-";
    }
    for(int i = num.start; i >= num.end; i--){
        out+=to_string(num.number[i]);
        if(i == 100){
            out+=".";
        }
    }
    os<<out;
    return os;
}

int BigNumber::firstNonZero(){
    for(int i = start; i >= end; i--){
        if(number[i] != 0){
            return i;
        }
    }
}

BigNumber::~BigNumber(){}















