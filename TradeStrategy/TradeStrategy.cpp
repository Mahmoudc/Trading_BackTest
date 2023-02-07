// TradeStrategy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;
void getInstBalance(double &balance, string &inst);
void calculateTradeToCsv(double& balance, string& inst, ofstream &myFile);
double findLot(string& inst);
int main()
{
    std::ofstream myfile;
 
  // myFile.open("trading_log.csv");
    double bal = 0;
    string inst = "";
    //Parameter first get insturment, and balance
    getInstBalance(bal, inst);
    myfile.open(inst+".csv");
    myfile << "Inst,";
    myfile << "Buy/Sell,";
    myfile << "Lot,";
    myfile << "Entry,";
    myfile << "Exit,";
    myfile << "Profit/Loss,";
    myfile <<"Balance: "<< bal;
    double maxLoss = bal - (bal * 0.08);
    double maxWin = bal + (bal * 0.08);
    cout << bal << endl;
    cout << inst << endl;
    cout << maxLoss << endl;
    //Now a loop that would ask for entry price, exit price, profits, and would break loop if account goes below 8%
    do
    {
        //Enter entry price, exit price, calculates profits, losses, substracts from balance and add's details to csv file with dates, and days
        calculateTradeToCsv(bal, inst, myfile);

    } while (bal > maxLoss&& bal<maxWin);
    myfile.close();
}
void calculateTradeToCsv(double& bal, string& inst, ofstream &myFile)
{
    double entry = 0, exit = 0;
    double isLong = 1;
    double lotSelected = 0;
    double lotBasedIns = findLot(inst);
    double diffPrice = 0;
    string date = "";
    //Figure out the lot as well as the calculation for it
    //No You'll get the time from charts
    cout << "Is position long or short(1, 0): ";
    cin >> isLong;
    cout << "Enter lot size for trade: ";
    cin >> lotSelected;
    cout << "Enter your entry price: ";
    cin >> entry;
    cout << "Enter your exit price: ";
    cin >> exit;
  /*  cout << "Enter the date trade has been entered: ";
    cin >> date;*/
    if (isLong == 1)
    {
        //Then compute buy
        diffPrice = exit - entry;
    }
    else if (isLong == 0)
    {
        //Compute short
        diffPrice = entry - exit;
    }
    double profitLoss = (lotSelected / (lotBasedIns)) * diffPrice;
    bal += profitLoss;
    if(diffPrice<0)
        cout << "Loss: "<<profitLoss << endl;
    else 
        cout << "Profit: " << profitLoss << endl;
    cout << "Current balance: " << bal << endl;
    //Csv
    

    // Send data to the stream
    myFile << "\n"+inst;
    if (isLong == 1)
        myFile << ",Buy";
    else
        myFile << ",Sell";
    myFile << ","<<lotSelected;
    myFile << "," << entry;
    myFile << "," << exit;
    myFile << ","<<profitLoss;
    myFile << "," << bal;

    // Close the file
}
void getInstBalance(double &bal, string &inst)
{
    cout << "Enter your starting balance: ";
    cin >> bal;
    cout << "\nEnter the instrument you'd like to trade: ";
    cin >> inst;
}
double findLot(string& inst)
{
    //If dollar on 1 lot is 100 then on 0.1 10, and 0.01 is 1
    if (inst == "XAUUSD")
    {
        return 0.01;//check how many 0.01 is on the lot that the user picked then multiply by 1 
    }
    else if (inst == "USDJPY")
    {
        return 0.001;//check how many 0.01 is on the lot that the user picked then multiply by 0.1
    }
    return 0.00001;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
