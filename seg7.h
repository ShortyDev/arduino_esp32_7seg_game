class Seg7
{
public:
    Seg7(int ss, int pwm);
    void begin();
    void on();
    void off();
    void displayRaw(int field1, int field2);
    void displayNumber(int num);
    
private:
    int _ss;
    int _pwm;
    int getHexFromNum(int num);
};
