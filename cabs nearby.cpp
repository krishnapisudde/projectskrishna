#include<bits/stdc++.h>
using namespace std;
#define latd1 12.9611159
#define lond1 77.6362214
#define pi 3.14159265358979323846
#define earth_radius 6371.0
ifstream customer_list("customers.json");
ofstream out("answer.json");

// function to convert degree to radian
double degree_to_radian(double deg)
{
    return (deg * pi / 180);
}

/* function to calculate distance between 2 given locations using great distance 
circle formula*/
double distanceEarth(double latd2,double lond2)
{
    double lat1,lon1,lat2,lon2,delta_lon,central_ang;
    lat1 = degree_to_radian(latd1);
    lon1 = degree_to_radian(lond1);
    lat2 = degree_to_radian(latd2);
    lon2 = degree_to_radian(lond2);

    delta_lon = lon2-lon1;
     
    // great circle distance formula
    central_ang = acos (sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(delta_lon));
    return (earth_radius * central_ang);
}
/* structure which contains data and functions for accessing and processing 
 data from given customers.json file.*/
struct json
{
    long long int length, i, j, x, y, m, n, f,fi , id[100000];
    //i and j are used to access various elements of char arrays.
    // x is used to measure the size of element of latitude_as_string array
    //  y is used to measure the size of element of longitude_as_string array
    // m is used to measure the size of elemewnt of id_as_string array
    // n is used to measure to size of element of name array 
    // f keeps count of " " "  symbol
    // fi keeps count of " : " symbol


    char latitude_as_string[1000];
    char longitude_as_string[1000];
    char id_as_string[1000];
    char name[1000];

    double latd2 , lond2;

    // to get each line of customers.json file as string 
    string line;

    // function to check whether distance between 2 points is less than 15 km or not
    void distance_find ()
    {
        if(distanceEarth(latd2,lond2) <= 15)
        {
            // converting id to int format 
            id[i] = atoll(id_as_string);
            i++;
            cout<<"{\"user_id\":"<<id[i-1]<<",\"name\":"<<name<<"}"<<"\n";
        }
    }
    /* function to read various attributes like latitude, longitude,name ,
     id ,etc from customers.json file. approach to get json attributes.*/

     void json_parser()
     {
        if(customer_list.is_open())
        {
            while (getline(customer_list,line))
            {
                f=0;x=0;y=0;fi=0;m=0;n=0;
                length = line.size();
                for (int i = 0; i < length; i++)
                {
                    if(line[i] == '"' )
                    {
                        f++;
                    }
                    else if(line[i] == ':')
                    {
                        fi++;
                    }
                    // to get latitude of location 
                    if(f==3)
                    {
                        i++;
                        while (line[i]!='"')
                        {
                            latitude_as_string[x] = line[i];
                            x++;j++;
                        }
                        i--;
                        latitude_as_string[x] = '\0';
                        
                    }

                    // to get longitude of location 
                    else if(f==13)
                    {
                        i++;
                        while (line[i]!= '"')
                        {
                            longitude_as_string[y] = line[i];
                            y++;i++;
                        }
                        i--;
                        longitude_as_string[y]='\0';
                        
                    }
                    // to get the name of friend

                    else if(fi==4)
                    {
                        i += 2;
                        while (line[i] !=',')
                        {
                            name[n] = line[i];
                            n++;i++;
                        }
                        i--;
                        name[n] = '\0';
                        fi++;
                        f += 2;
                    }
                }
                // converting latitude and longitude in string to float

                latd2 = atof(latitude_as_string);
                lond2 = atof(longitude_as_string);
                distance_find();
                
            }
            
        }
        // closing stream of customer's file.
        customer_list.close();

        // closing stream of answer's file.
        out.close() ;
    }
};
int main()
{
    // creating object of the structure json
    json obj;

    // to read customers.json file
    obj.json_parser();
    
    return 0;
}