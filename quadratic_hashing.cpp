#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>

#define TABLE_SIZE 10007
using namespace std;




template <class T>
class  Table{
	T SECRET_WORD;		//no other data entry should be equal to the SECRET_WORD.
public:
	T my_table[TABLE_SIZE];
	int h(long long int k);						//auxiliary function
	int h(long long int k,int i);				//original hash function
	long long int generate_value(T &data);		//creates an long integer corresponding to each data.Need not be unique for each entry(data)
	int compare(T &data_1,T &data_2);			//each time,this should be modified for different type of data structure.
	Table();
	int search(T &data_in_table);			//returns the key of the data in the table. -1 if data is not in the Table
	int insert_data(T new_value);			//returns -1 if data is not in the table else the key of the data.
	int delete_data(T data_in_table);		//empty out the Table entry,returns 0 if data is not in the table.
	T get_value(int key);
};

//construtor
template<class T>
Table<T>::Table(){
	SECRET_WORD="-1";
	for(int i=0;i<TABLE_SIZE;i++)
		my_table[i]="";
}


template<typename T>
int Table<T>::delete_data(T data_in_table){
	int index=search(data_in_table);
	if(index!=-1){
		my_table[index]=SECRET_WORD;
		cout<<"Entry:\""<<data_in_table<<"\" deleted successfully"<<endl;
		return index;
	}
	else {
		cout<<"No data with the value: "<<data_in_table<<endl;
		return -1;
	}
}

template<typename T>
int Table<T>::search(T &data){
	long long int value=generate_value(data);
	int iteration_num=0;
	string p=my_table[h(value)];
	while(true){
	//	cout<<"P is::"<<"."<<endl;
	//	cout<<"compare returns"<<p.compare("")<<endl;
		if(p.compare("")==0){
	//		cout<<"HERE"<<endl;
			return -1;
		}
		else if(p.compare(data)==0)
			return h(value,iteration_num);		//position at which data resides
		p=my_table[h(value,++iteration_num)];
		if(iteration_num > TABLE_SIZE){
			cout<<"Search:There's some problem with the Table entries or the hash function or the table maybe full!"<<endl;
			return -1;
		}
	}
	
}

/*Copy of the data is inserted in the table. Duplicate of a data is not supported */
template<typename T>
int Table<T>::insert_data(T data){
	if(search(data)!=-1){
		cout<<"Data is already in the table"<<endl;
		return -1;
	}
	long long int value=generate_value(data);
	int iteration_num=0;
	string p=my_table[h(value)];
	while( true){
		if(p.compare("")==0){
			my_table[h(value,iteration_num)]=data;
			cout<<"Entry:\""<<data<<"\" deleted successfully"<<endl;
			return h(value,iteration_num);
		}
		else if(p.compare(SECRET_WORD)==0){
			my_table[h(value,iteration_num)]=data;
			cout<<"Entry:\""<<data<<"\" deleted successfully"<<endl;
			return h(value,iteration_num);
		}
		p=my_table[h(value,++iteration_num)];
		if(iteration_num > TABLE_SIZE){
			cout<<"There's some problem with the Table entries or the hash function or the table maybe full!"<<endl;
			return -1;
		}
	}

	//data copying...
	//check here
	//maybe unsupported for different data types.
	my_table[h(value,iteration_num)]=data;
	return h(value,iteration_num);		//position at which data resides
}


/*Hash functions for quadratic probing*/
//check here


template<class T>
int Table<T>::h(long long int k){
	return k%TABLE_SIZE;
}

template<class T>
int Table<T>::h(long long int k,int i){
	return (h(k)+(i*(i+1))/2)%TABLE_SIZE;
}

template <typename T>
/*Assumes the data structure to be a string*/
/* returns > 0 if a > b (lexicographically.)*/
int Table<T>::compare(T &a,T &b){
	return a.compare(b);
}

//this function should be modified each time depending upon "data" structure.
//assuming data is a string here.
template<class T>
long long int Table<T>::generate_value(T &data){
	/*ASSUMING DATA IS OF TYPE STRING*/
	/*otherwise implement a toString() for data */
	/*string data_modified=data.toString()*/
	long long int value=0;
	long long int pow=1;
	long long int BIG_LONG_INT=(1l<<55);
	
	for(int i=0;i<data.length();i++){
		value+=(int)(data[i]-'a')*pow;
		pow*=10;
		if(pow > BIG_LONG_INT)
			pow=1;
	}
	//to see what's generated...
	value*=value<0?-1:1;
//	cout<<"Key:"<<data<<" value:"<<value<<endl;
	return value;
}


//main driver to check the functions of the table.

int main(){
	int size=350;
	string StudentNames[]={"Etha Shellman", "Breana Bowens ", "Suzette Keo", "Shaquita Heid ", "Loria Jong ", "Otha Tirrell ", "Chiquita Shawn ", "Gertie Langenfeld ", "Annie Wainscott ", "Gisela Goggans ", "Antonietta Edelman ", "Dustin Songer ", "Elfriede Mar ", "Lyndia Just ", "Karena Decamp ", "Jo Iversen ", "Hipolito Posner ", "Letha Lugar ", "Akiko Cable ", "Kathline Woodberry ", "Kenyetta Martyn ", "Cristie Boone ", "Mark Knapper ", "Diann Calle ", "Madie Heuser ", "Lakeshia Degroot ", "Barbara Ables ", "Lynetta Mayo ", "Andree Egbert ", "Jody Dement ", "Eustolia Aldrete ", "Dreama Blue ", "Leta Stockbridge ", "Tory Fabiano ", "Yoko Kiser ", "Natashia Steffan ", "Wynell Mcie ", "Wilmer Hussain ", "Georgann Conboy ", "Belle Leonardi ", "Socorro Crossley ", "Basil Meredith ", "Bradley Westhoff ", "Nakisha Batt ", "Junita Seder ", "Efrain Arenas ", "Anita Schultze ", "Velda Ramon ", "Octavia Blackston ", "Shan Myers", "Albina", "Trimpe", "Brandee", "Billman", "Jacques", "Fazio", "Peggy", "Meaux", "Racquel", "Moline", "Barry", "Obannon", "Mary", "Wingerter", "Retha", "Lastinger", "Mayra", "Pass", "Jannet", "Mckim", "Dionna", "Cortese", "Lee", "Schmid", "Bertha", "Bunner", "Tawny", "Bowerman", "Ricarda", "Lones", "Rodger", "Sly", "Norberto", "Currington", "Kasie", "Giorgi", "Lorrie", "Neel", "Ian", "Kellison", "Lanelle", "Mclain", "Barbera", "Glasser", "Allegra", "Clemens", "Kelly", "Miles", "Pablo", "Upshaw", "Jenice", "Hehn", "Alline", "Malbon", "Brynn", "Abele", "Moira", "Spafford", "Adam", "Bergeson", "Von", "Cocklin", "Luna", "Victor", "Audra", "Swartwood", "Leatha", "Kurland", "Leif", "Colorado", "Kay", "Burchill", "Gerard", "Victory", "Meryl", "Laine", "Clarine", "Strope", "Tonda", "Macke", "Cristobal", "Ricken", "Candyce", "Hutter", "Keli", "Eisert", "Fidela", "Eakes", "Maritza", "Schult", "Jerri", "Rozelle", "Lavon", "Summerfield", "Rebecca", "Grier", "Bryan", "Collum", "Ron", "Squillante", "Misty", "Lien", "Elouise", "Arehart", "Edwina", "Borey", "Hoa", "Aubrey", "Annamarie", "Tignor", "Waltraud", "Emberton", "Tracee", "Riegel", "Yvette", "Peters", "Willetta", "Brehm", "Janis", "Chattin", "Manual", "Shaeffer", "Georgeanna", "Baez", "Johnathan", "Ahmad", "Ivana", "Horwitz", "Tennie", "Fetterolf", "Ezequiel", "Rabalais", "Angelique", "Halladay", "Gil", "Rhoten", "Tamra", "Devries", "Ivelisse", "Figaro", "Verna", "Eden", "Katina", "Edgecomb", "Gustavo", "Claypool", "Hildegarde", "Nickols", "Ka", "Herdon", "Dani", "Bullen", "Joycelyn", "Windholz", "Shirely", "Rueda", "Jayme", "Paulus", "Rosalia", "Stickler", "Keisha", "Payan", "Tabatha", "Yandell", "Pearline", "Detwiler", "Shea", "Ratti", "Joella", "Kari", "Artie", "Vroman", "Kenny", "Shive", "Robyn", "Villanueva", "Dorthy", "Wollman", "Emerita", "Laporta", "Lorri", "Grass", "Tamara", "Hennessee", "Ada", "Lacroix", "Fern", "Frazee", "Latia", "Winkle", "Enoch", "Conwell", "Glennis", "Monnin", "Narcisa", "Wilcoxson", "Zachary", "Vanhook", "Li", "Throop", "Karyn", "Sica", "Nannie", "Lizarraga", "Setsuko", "Bellew", "Maude", "Lenton", "Marylou", "Truby", "Kayleigh", "Schlicher", "Doretta", "Malecha", "Jeannine", "Streeter", "Beatris", "Schleusner", "Valorie", "Terrel", "Ben", "Storms", "Philip", "Marcelino", "Agustina", "Hunley", "Cathrine", "Obrian", "Johnette", "Hollar", "Riva", "Farr", "Nida", "Wyer", "Mirna", "Dozal", "Clarinda", "Procter", "Roland", "Gover", "Malcom", "Hagar", "Josette", "Schober", "Shirely", "Debelak", "Stephenie", "Dickman", "Karren", "Malcom", "Roman", "Lamacchia", "Veta", "Costanza", "Katie", "Daigneault", "Imogene", "Schlabach", "Shavon", "Blaylock", "Melani", "Hudkins", "Aletha", "Strum", "Alfonso", "Vanwinkle", "Jason", "Funnell", "Rosalinda", "Nourse", "Antione", "Staple", "Maurine", "Powers", "Christena", "Lukasik", "Christinia", "Conely", "Ismael", "Moyle", "Alanna", "Dower", "Stephen", "Lawton", "Kelley", "Schaefer", "Yu", "Jernigan", "Deonna", "Dewey", "Alexa", "Hagemann", "Kiley", "Cockrum", "Elden", "Godsey", "Ronda", "Rahe", "Kristan", "Higby"};
	int j;
	Table<string> my_hash_table;
	srand(time(NULL));
	for(int i=0;i<size;i++){
		j=rand();
		if(j%2 == 0)
			my_hash_table.insert_data(StudentNames[rand()%size]);
		else my_hash_table.delete_data(StudentNames[rand()%size]);
	}
	return 0;
}