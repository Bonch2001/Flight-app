#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

class Flight
{
public:
    string departure;
    string destination;
    int hour;
    int min;
    int day;
    int month;
    int year;
    int price;
    Flight(string a, string b, int c, int d, int e, int f, int g, int h)
    {
        this->departure = a;
        this->destination = b;
        this->hour = c;
        this->min = d;
        this->day = e;
        this->month = f;
        this->year = g;
        this->price = h;
    }
    void print()
    {
        cout<<this->departure<<" "<<this->destination<<" "<<this->hour<<" "<<this->min<<" "<<this->day<<" "<<this->month<<" "<<this->year<<" "<<this->price<<endl;
    }
};

string passwdIO()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    string input;
    getline(cin, input);
    SetConsoleMode(hStdin, mode);
    return input;
}

char start()
{
    cout<<"Pentru operator introduceti 1, pentru utilizator introduceti 2: ";
    fflush(stdin);
    char r = getch();
    if (r == '1')
    {
        cout<<"\nAcum sunteti in modul OPERATOR"<<endl;
    }
    else if (r == '2')
    {
        cout<<"\nAcum sunteti in modul UTILIZATOR"<<endl;
    }
    else
    {
        cout<<"Eroare!"<<endl;
        return -1;
    }
    return r;
}

int gcd(int a, int h)
{
    int temp;
    while(1)
    {
        temp = a%h;
        if(temp==0)
            return h;
        a = h;
        h = temp;
    }
}

int rsa_enc(int x)
{
    double p = 3;
    double q = 7;
    double n=p*q;
    double count;
    double totient = (p-1)*(q-1);
    double e=5;
    while(e<totient)
    {
        count = gcd(e,totient);
        if(count==1)
            break;
        else
            e++;
    }
    double k = 2;
    double d = (1 + (k*totient))/e;


    double c = pow(x,e);
    double enc=fmod(c,n);

    return (enc);
}

int rsa_dec(int y)
{
    double p = 3;
    double q = 7;
    double n=p*q;
    double count;
    double totient = (p-1)*(q-1);
    double e=5;
    while(e<totient)
    {
        count = gcd(e,totient);
        if(count==1)
            break;
        else
            e++;
    }
    double k = 2;
    double d = (1 + (k*totient))/e;

    double m = pow(y,d);
    double dec=fmod(m,n);

    return dec;
}

int main()
{
    string n, p, z, w;
    vector<string> a, names, b;
    int i, j, c[6], d, kon;
    int passwords[10][20], passwords_input[20];
    char r, q, s;
    vector<Flight> v, y;

init:
    q = start();
    if(q == '1')
    {
login1:
        try
        {
            fflush(stdin);
            cout<<"Nume utilizator: ";
            getline(cin, n);
            if(n != "admin")
                throw n;
        }
        catch (string s)
        {
            cout<<"Nume de utilizator gresit!"<<endl;
            goto login1;
        }

password1:
        try
        {
            fflush(stdin);
            cout<<"Parola: ";
            p = passwdIO();
            if (p != "12345678")
                throw p;
            else
                cout<<"\nAutentificare reusita! Acum puteti edita zboruri.\n=========MENIU========="<<endl;
        }
        catch (string s)
        {
            cout<<"\nParola gresita!"<<endl;
            goto password1;
        }

        cout<<"1. Vizualizare zboruri existente\n2. Adaugare zbor\n3. Stergere zbor\n4. Log out (iesire mod operator)\n";
meniu_operator:
        r = getch();
        if(r == '1')
        {
            int num = 0;
            cout<<"Zboruri existente:\n";
            for (auto & element : v)
            {
                cout<<num++<<". ";
                element.print();
            }
            goto meniu_operator;
        }
        else if (r == '2')
        {
            cout<<"\nAtentie! Respectati formatul zborului:\nAEROPORT_PLECARE AEROPORT_DESTINATIE ORA MINUTE ZI LUNA AN PRET\n";
            cout<<"Introduceti datele zborului ce urmeaza a fi adaugat:\n";
            getline(cin, z);
            istringstream iss(z);
            while(iss >> w)
            {
                a.push_back(w.c_str());
            }
            j = 0;
            for (i=2; i<8; i++)
            {
                c[j] = stoi(a[i]);
                j++;
            }

            if(c[0]>23 || c[0]<0 || c[1]>59 || c[1]<0)
            {
                cout<<"Format ora invalid!\n";
                goto meniu_operator;
            }
            if(c[2]>31 || c[2]<1 || c[3]>12 || c[3]<1 || c[4]>2022 || c[4]<2021)
            {
                cout<<"Format data invalid!\n";
                goto meniu_operator;
            }
            if (c[2] <= 15 && c[3]<=12 && c[4] <= 2021)
            {
                cout<<"Data in trecut!\n";
                goto meniu_operator;
            }
            Flight x(a[0],a[1],c[0],c[1],c[2],c[3],c[4],c[5]);
            v.push_back(x);
            cout<<"Zbor adaugat cu succes!"<<endl;
            a.clear();
            goto meniu_operator;
        }
        else if (r == '3')
        {
            cout<<"Introduceti numarul zborului ce va fi anulat: "<<endl;
            fflush(stdin);
            cin>>i;
            if (i > v.size() - 1)
            {
                cout<<"Zborul cu numarul introdus nu exista!"<<endl;
                goto meniu_operator;
            }
            else
            {
                vector<Flight>::iterator it;
                it = v.begin() + i;
                v.erase(it);
                cout<<"Zbor sters!"<<endl;
                goto meniu_operator;
            }
        }
        else if (r == '4')
        {
            goto init;
        }
        else
        {
            cout<<"Eroare!"<<endl;
            goto meniu_operator;
        }
    }

    else if (q == '2')
    {
uuu:
        cout<<"======MENIU======"<<endl;
        cout<<"1. Log in\n2. Creare cont\n3. Iesire mod utilizator\n";
        r = getch();
        int index = -1;
        if (r == '1')
        {
login2:
            try
            {
                fflush(stdin);
                cout<<"Nume utilizator: ";
                fflush(stdin);
                getline(cin, n);
                auto it = find(names.begin(), names.end(), n);
                if (it != names.end())
                    index = it - names.begin();
                else
                    throw n;
            }
            catch (string s)
            {
                cout<<"Numele de utilizator introdus nu exista!"<<endl;
                goto login2;
            }

password2:
            try
            {
                fflush(stdin);
                cout<<"Parola: ";
                p = passwdIO();
                d = p.length();
                for (kon = 0; kon < d; kon++)
                {
                    passwords_input[kon] = rsa_enc(p[kon]);
                }
                int vv = 1;
                for (kon = 0; kon < d && vv == 1; kon++)
                {
                    if(passwords_input[kon] != passwords[index][kon])
                        vv = 0;
                }
                if (vv)
                    throw p;
                else
                    cout<<"\nAutentificare reusita! Acum puteti cauta si rezerva zboruri.\n=========MENIU========="<<endl;
            }
            catch (string p)
            {
                cout<<"\nParola gresita!"<<endl;
                goto password2;
            }
            cout<<"1. Vizualizare zboruri existente\n2. Cautare zbor\n3. Rezervare zbor\n4. Vizualizare zboruri rezervate\n5. Log out\n";
meniu_utilizator:
            s = getch();
            if (s == '1')
            {
                int num = 0;
                cout<<"Zboruri existente:\n";
                for (auto & element : v)
                {
                    cout<<num++<<". ";
                    element.print();
                }
                goto meniu_utilizator;
            }
            else if(s == '2')
            {
                cout<<"\nAtentie! Respectati formatul zborului:\nAEROPORT_PLECARE AEROPORT_DESTINATIE ORA MINUTE ZI LUNA AN PRET\n";
                getline(cin, z);
                istringstream iss(z);
                while(iss >> w)
                {
                    b.push_back(w.c_str());
                }
                int sw = 0;
                for (auto & e : v)
                {
                    if(e.departure == b[0] && e.destination == b[1] && e.hour == stoi(b[2]) && e.min == stoi(b[3]) && e.day == stoi(b[4]) && e.month == stoi(b[5]) && e.year == stoi(b[6]) && e.price == stoi(b[7]))
                    {
                        cout<<"Zborul cautat exista: ";
                        e.print();
                        sw = 1;
                        b.clear();
                        goto meniu_utilizator;
                    }
                }
                if (sw == 0)
                {
                    cout<<"Zborul cautat nu exista!"<<endl;
                    b.clear();
                    goto meniu_utilizator;
                }
            }
            else if (s == '3')
            {
                cout<<"Introduceti numarul zborului ce va fi rezervat: "<<endl;
                fflush(stdin);
                cin>>i;
                if (i > v.size())
                {
                    cout<<"Zborul cu numarul introdus nu exista!"<<endl;
                    goto meniu_utilizator;
                }
                vector<Flight>::iterator it;
                it = v.begin() + i;
                //y.push_back(v[it]);   //no idea why it does not work :(
                cout<<"Zbor rezervat!"<<endl;
                goto meniu_utilizator;
            }
            else if (s == '4')
            {
                cout<<"Zboruri rezervate:\n";
                for (auto & element : y)
                {
                    element.print();
                }
                goto meniu_utilizator;
            }
            else if (s == '5')
            {
                goto uuu;
            }
            else
            {
                cout<<"Eroare!"<<endl;
                goto meniu_utilizator;
            }
        }
        else if (r == '2')
        {
creare_cont:
            try
            {
                fflush(stdin);
                cout<<"Introduceti adresa de e-mail: ";
                getline(cin, z);
                d = z.length();
                char char_array[d + 1];
                strcpy(char_array, z.c_str());
                if (strchr(char_array, '@') == NULL)
                    throw z;
                names.push_back(z);
            }
            catch (string z)
            {
                cout<<"Adresa de e-mail invalida!"<<endl;
                goto creare_cont;
            }
            try
            {
                fflush(stdin);
                cout<<"Introduceti parola: ";
                p = passwdIO();
                d = p.length();
                if (d < 6)
                    throw d;
                cout<<"\nIntroduceti iar parola: ";
                fflush(stdin);
                w = passwdIO();
                if (p != w)
                    throw w;
                for (kon = 0; kon < d; kon++)
                {
                    int criptat = rsa_enc(p[kon]);
                    passwords[index][kon] = criptat;
                }
            }
            catch (string p)
            {
                cout<<"\nParolele nu corespund!"<<endl;
                goto creare_cont;
            }
            catch (int nr)
            {
                cout<<"\nParola prea slaba!"<<endl;
                goto creare_cont;
            }
            cout<<"\nContul a fost creat cu succes!"<<endl;
            goto uuu;
        }
        else if (r == '3')
        {
            goto init;
        }
        else
        {
            cout<<"Eroare!"<<endl;
        }
    }
    return 0;
}
