#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

const char path[] = "game/Stones.txt";
vector<int> chooseLevel(const char* f, int level){
    vector<vector<int>>data;
    ifstream infile(f);
    string line;
    while(getline(infile,line)){
        vector<int>tmp;
        int value;
        stringstream iss(line);
        while(iss>>value){
            tmp.push_back(value);
        }
        data.push_back(tmp);
    }
    int maxlevel = data.size();
    int num;
    if (level > maxlevel) num = rand() % maxlevel;
    else num = level-1;
    vector<int>a;
    for (int i=0; i<data[num][0];i++){
        a.push_back(data[num][i+1]);
    }
    return a;
}

class Player {
private:
    string name;
    string type; //loai ng choi AI, human,...
    int mode; //mode choi ...vs...
    int id; //nguoi choi so 1 hay so 2
    bool Isyourturn;
    bool Isthewinner;
public:
    string getname() const {
        return name;
    }
    //virtual void getName() = 0;
    void setName(string _name){
        name = _name;
    }
    void setType(string _type){
        type = _type;
    }
    void setId(int _id){
        id = _id;
    }
    void setMode(int _mode){
        mode = _mode;
    }
    //virtual void getType() = 0;
    void setTurn(int turn){
        if (id==turn) Isyourturn = true;
        else Isyourturn = false;
    }
    void setIsthewinner(int winner){
        if (id==winner) Isthewinner = true;
        else Isthewinner = false;
    }
    virtual void move(vector<int>& matrix) = 0;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(){
        setType("Human");
    }
    void move(vector<int>& matrix){
        int pile, stones;
        do {
            cout << getname() << " lay tu coc so: ";
            cin >> pile;
        } while (!hoplepile(matrix,pile));

        do {
            cout << getname() << " lay bao nhieu vien: ";
            cin >> stones;
        } while (!hoplestone(matrix,pile,stones));

        matrix[pile-1] -= stones;
    }
    void getName(){
        cout << "Enter your username: ";
        string _name;
        cin >> _name;
        setName(_name);
    }
    bool hoplepile(const vector<int>& matrix, const int &pile){
        if (pile>=1 && pile <= matrix.size() && matrix[pile-1]>0) return true;
        return false;
    }
    bool hoplestone(const vector<int>& matrix, const int &pile, const int &stones){
        if (matrix[pile-1]>=stones) return true;
        return false;
    }
};

class AIPlayer : public Player {
public:
    AIPlayer(){
        setType("AIPlayer");
        setName("AIPlayer");
    }
    void move(vector<int>& matrix){
        int pile, stones=0;
        int Npiles = matrix.size();
        while (stones==0){
            pile = rand() % Npiles;
            if (matrix[pile]) stones = rand() % (matrix[pile]) + 1;
        }
        matrix[pile] -= stones;
        cout << getname() << " lay " << stones << " vien da tu coc " << pile + 1 << endl;
    }
};

class SmartAIPlayer : public Player {
public:
    SmartAIPlayer(){
        setType("SmartAIPlayer");
        setName("SmartAIPlayer");
    }
    bool RemainOnePile(const vector<int>& matrix){
        int size = matrix.size();
        int count = 0;
        for (int i=0; i<size; i++){
            if (matrix[i] != 0) count++;
        }
        if (count == 1) return true;
        return false;
    }
    void moveOnePile(vector<int>& matrix){
        int index;
        int size = matrix.size();
        for (int i=0; i<size; i++){
            if (matrix[i]>0){
                index = i;
                break;
            }
        }
        cout << getname() << " lay " << matrix[index] << " vien da tu coc " << index + 1 << endl;
        matrix[index] = 0;
    }
    bool RemainTwoPiles(const vector<int>& matrix){
        int size = matrix.size();
        int count = 0;
        for (int i=0; i<size; i++){
            if (matrix[i] != 0) count++;
        }
        if (count == 2) return true;
        return false;
    }
    void moveTwoPiles(vector<int>& matrix){
        int index1, index2;
        int size = matrix.size();
        for (int i=0; i<size; i++){
            if (matrix[i]>0){
                index1 = i;
                break;
            }
        }
        for (int i=index1+1; i<size; i++){
            if (matrix[i]>0){
                index2 = i;
                break;
            }
        }
        if (matrix[index1]>matrix[index2]){
            cout << getname() << " lay " << matrix[index1] - matrix[index2] << " vien da tu coc " << index1 + 1 << endl;
            matrix[index1]=matrix[index2];
        }
        else if (matrix[index1]<matrix[index2]){
            cout << getname() << " lay " << matrix[index2] - matrix[index1] << " vien da tu coc " << index2 + 1 << endl;
            matrix[index2]=matrix[index1];
        }
        else{
            int pile, stones=0;
            while (stones==0){
                pile = index1;
                stones = rand() % (matrix[pile]) + 1;
            }
            matrix[pile] -= stones;
            cout << getname() << " lay " << stones << " vien da tu coc " << pile + 1 << endl;
        }
    }
    int NimSum(const vector<int>& matrix){
        int sum = 0;
        int size = matrix.size();
        for (int i=0; i<size; i++){
            sum = sum ^ matrix[i];
        }
        return sum;
    }
    bool IsgoodPos(int NimSum){
        if (NimSum != 0) return true;
        return false;
    }
    vector<int> XOR(const vector<int>& matrix){
        int size = matrix.size();
        vector<int>a;
        int nimsum = NimSum(matrix);
        for (int i=0; i< size; i++){
            int tmp = nimsum ^ matrix[i];
            a.push_back(tmp);
        }
        return a;
    }
    void move(vector<int>& matrix){
        if (RemainOnePile(matrix)) moveOnePile(matrix);
        else if (RemainTwoPiles(matrix)) moveTwoPiles(matrix);
        else {
            int nimsum = NimSum(matrix);
            if (IsgoodPos(nimsum)){
                vector<int>x = XOR(matrix);
                int size = matrix.size();
                int index;
                for (int i=0; i<size; i++){
                    if (matrix[i]>x[i]){
                        index = i;
                        break;
                    }
                }
                cout<< getname() << " lay " << matrix[index] - x[index] << " vien da tu coc " << index + 1 << endl;
                matrix[index] = x[index];
            }
            else {
                int pile, stones=0;
                int Npiles = matrix.size();
                while (stones==0){
                    pile = rand() % Npiles;
                    if (matrix[pile]) stones = rand() % (matrix[pile]) + 1;
                }
                matrix[pile] -= stones;
                cout << getname() << " lay " << stones << " vien da tu coc " << pile + 1 << endl;
            }
        }
    }
};

class Game{
private:
    int NumOfPiles;
    vector<int>Stones;
    int playMode;
    HumanPlayer human1;
    HumanPlayer human2;
    AIPlayer AI;
    SmartAIPlayer smart;
    int level;
    int turn;
public:
    void setMode(){
        cout << "Type of game: ";
        cin >> playMode; //3 = smart vs human
    }
    int getMode(){
        return playMode;
    }

    void setLevel(){
        cout << "Level of game: ";
        cin >> level;
    }
    int getLevel(){
        return level;
    }

    void setStones(){
        Stones = chooseLevel(path,level);
        NumOfPiles = Stones.size();
    }
    vector<int> getStones(){
        return Stones;
    }

    void setPlayers(){
        if (playMode == 1) { //human vs human
            human1.setId(1);
            human1.getName();
            human2.setId(2);
            human2.getName();
        }
        else if (playMode == 2) { //AIPlayer vs human
            AI.setId(1);
            human2.setId(2);
            human2.getName();
        }
        else if (playMode == 3) { //SmartAIPlayer vs human
            smart.setId(1);
            human2.setId(2);
            human2.getName();
        }
    }
   // vector<Player> getPlayers(){
     //   return players;
    //}

    void in(){
        for (int i=0; i<Stones.size(); i++){
            cout << "Pile " << i+1 << " : ";
            for (int j=1; j<=Stones[i]; j++){
                cout << "O ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool checkWin(){
        bool check = 1;
        for (int i=0; i<Stones.size(); i++){
            if (Stones[i]>0) {
                check = 0;
                break;
            }
        }
        return check;
    }

    void step(){
        if (playMode == 1) {
            if (turn == 1) {
                human1.move(Stones);
                turn = 2;
            } else {
                human2.move(Stones);
                turn = 1;
            }
            human1.setTurn(turn);
            human2.setTurn(turn);
        }

        else if (playMode == 2) {
            if (turn == 1) {
                AI.move(Stones);
                turn = 2;
            } else {
                human2.move(Stones);
                turn = 1;
            }
            AI.setTurn(turn);
            human2.setTurn(turn);
        }

        else if (playMode == 3) {
            if (turn == 1) {
                smart.move(Stones);
                turn = 2;
            } else {
                human2.move(Stones);
                turn = 1;
            }
            smart.setTurn(turn);
            human2.setTurn(turn);
        }
    }

    void winner(){
        if (playMode == 1){
            if (turn == 2) cout << "The winner is " << human1.getname() << endl;
            else cout << "The winner is " << human2.getname() << endl;
        }

        else if (playMode == 2){
            if (turn == 2) cout << "The winner is " << AI.getname() << endl;
            else cout << "The winner is " << human2.getname() << endl;
        }

        else if (playMode == 3){
            if (turn == 2) cout << "The winner is " << smart.getname() << endl;
            else cout << "The winner is " << human2.getname() << endl;
        }
    }

    void play(){
        setMode();
        setLevel();
        setStones();
        setPlayers();
        cout << "Choose who has the first turn: ";
        cin >> turn;
        if (turn == 3) turn = rand()%2 +1; //turn = 3 is random
        if (playMode == 1){
            human1.setTurn(turn);
            human2.setTurn(turn);
        }
        else if (playMode == 2){
            AI.setTurn(turn);
            human2.setTurn(turn);
        }
        else if (playMode == 3){
            smart.setTurn(turn);
            human2.setTurn(turn);
        }
        in();
        while (checkWin()==0){
            step();
            in();
            if (checkWin()==1) winner();
        }
    }
};

int main() {
    Game game1;
    game1.play();
    return 0;
}
