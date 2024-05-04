#define F_CPU 8000000UL 
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>

// Define the pins used for the LCD display
#define LCD_RS PE2
#define LCD_RW PE1
#define LCD_EN PE0
/*
#define LCD_D0 PD0
#define LCD_D1 PD1
#define LCD_D2 PD2
#define LCD_D3 PD3
#define LCD_D4 PD4
#define LCD_D5 PD5
#define LCD_D6 PD6
#define LCD_D7 PD7*/

// Define the pins used for the keypad
#define KEYPAD_ROW0 PK0
#define KEYPAD_ROW1 PK1
#define KEYPAD_ROW2 PK2
#define KEYPAD_COL0 PK4
#define KEYPAD_COL1 PK5
#define KEYPAD_COL2 PK6
/*
// Define the pins used for the keypad
#define KEYPAD_ROW0 PB0
#define KEYPAD_ROW1 PB1
#define KEYPAD_ROW2 PB2
#define KEYPAD_ROW3 PB3
#define KEYPAD_COL0 PB4
#define KEYPAD_COL1 PB5
#define KEYPAD_COL2 PB6
#define KEYPAD_COL3 PB7*/


// Define the pins used for the money slot
#define MONEY_SLOT_MOTOR_PIN PF0

// Define the pins used for the fridge motor
#define FRIDGE_MOTOR_PIN PF1

// Define the number of tourists allowed in the park
#define PARK_CAPACITY 100

// Define the cost of a bottle of water
#define WATER_COST 1500

// Define the password for accessing the fridge replenishment function
#define FRIDGE_REPLENISHMENT_PASSWORD "123456"

// Define the serial console menu options
#define MENU_OPTION_1 "How many tourists, categorized by age group, are in the park?"
#define MENU_OPTION_2 "Which vehicles are still in the park?"
#define MENU_OPTION_3 "How much has been collected by the park aggregated by the fridge money and entrance fund?"
#define MENU_OPTION_4 "How many drivers are in the park?"
#define MENU_OPTION_5 "Number of bottles in the fridge"
#define MENU_OPTION_6 "Replenish Fridge"
#define MENU_OPTION_7 "Login"
#define MENU_OPTION_8 "How many cars are waiting outside the park?"
#define MENU_OPTION_9 "Is park full or not"

// Declare global variables
int num_children_in_park = 0;
int num_adults_in_park = 0;
int num_drivers_in_park = 0;
int num_vehicles_in_park = 0;
int num_bottles_in_fridge = 0;
int total_money_collected = 0;
int fridge_money_collected = 0;
int entrance_fee_collected = 0;
int park_full = 0;
// Define a structure to represent a vehicle
struct Vehicle {
	char type[20];
	char number_plate[10];
	//int childcount
	// Add more fields as needed
};

// Declare an array to store vehicles in the park
struct Vehicle vehicles_in_park[100];  // Adjust the array size as needed




void send_lcd_command(unsigned char command) {
	PORTA= command;
	// Set the RS pin to low to indicate that a command is being sent
	PORTB &= ~(1 << 2);// COMMAND MODE
	PORTB &= ~(1 << 1);// WRITE MODE
	PORTB |= (1 << 0); // Enable the LCD display
	_delay_ms(5); // Delay for 1 millisecond
	PORTB &= ~(1 << 0); // Disable the LCD display

}

void send_lcd_data(unsigned char data) {
	PORTA= data;
	// Set the RS pin to low to indicate that a command is being sent
	PORTB |=(1 << 2);// DATA MODE
	PORTB &= ~(1 << 1);// WRITE MODE
	PORTB |= (1 << 0); // Enable the LCD display
	_delay_ms(5); // Delay for 1 millisecond
	PORTB &= ~(1 << 0); // Disable the LCD display

}


// Function to initialize the LCD display
void init_lcd() {
	// Send the LCD initialization commands
	send_lcd_command(0x38); // Set the display mode to 2 lines with 5x7 dots
	send_lcd_command(0x0E); // Turn on the display
	send_lcd_command(0x06); // Set the cursor direction to right
	send_lcd_command(0x01); // Clear the display
}

// Function to send a command to the LCD display


// Function to send a character to the LCD display
void lcd_print(char info[]) {
	for (int i=0; i<strlen(info); i++){
		send_lcd_data(info[i]);
	}
	
}


// Function to print a string to the LCD display
/*
void print_lcd_string(char *string) {
	int i = 0;
	while (string[i] != '\0') {
		send_lcd_char(string[i]);
		i++;
	}
}*/



// Function to read a key from the keypad
/*
char read_key() {
	// Set the keypad row pins to output mode
	DDRK |= (1 << KEYPAD_ROW0) | (1 << KEYPAD_ROW1) | (1 << KEYPAD_ROW2) ;

	// Set the keypad column pins to input mode with pull-up resistors
	PORTK &= ~((1 << KEYPAD_COL0) | (1 << KEYPAD_COL1) | (1 << KEYPAD_COL2) );
	PORTK |= (1 << KEYPAD_COL0) | (1 << KEYPAD_COL1) | (1 << KEYPAD_COL2) ;


	// Scan the keypad rows
	for (int i = 0; i < 3; i++) {
		// Set the current row pin to low
		PORTK &= ~(1 << (KEYPAD_ROW0 + i));

		// Read the keypad column pins
		for (int j = 0; j < 3; j++) {
			if ((PINK & (1 << (KEYPAD_COL0 + j)) )== 0) {
				// A key has been pressed
				// Calculate and return the key value (you need to implement this)
				return '0' + (3 * i) + j + 1;
			}
		}

		// Set the current row pin to high
		PORTK |= (1 << (KEYPAD_ROW0 + i));
	}
	// No key has been pressed
	return '\0';
}*/


int read_key() {
	PORTK =0B11111110;
	if((PINK & (1<<4))==0){
		return 1;
	}
	if((PINK & (1<<5))==0){
		return 4;
	}
	if((PINK & (1<<6))==0){
		return 7;
	}
	if((PINK & (1<<7))==0){
		return 100;
	}
	
	
	
	PORTK =0B11111101;
	if((PINK & (1<<4))==0){
		return 2;
	}
	if((PINK & (1<<5))==0){
		return 5;
	}
	if((PINK & (1<<6))==0){
		return 8;
	}
	if((PINK & (1<<7))==0){
		return 0;
	}
	
	
	PORTK =0B11111011;
	if((PINK & (1<<4))==0){
		return 3;
	}
	if((PINK & (1<<5))==0){
		return 6;
	}
	if((PINK & (1<<6))==0){
		return 9;
	}
	if((PINK & (1<<7))==0){
		return 300;
	}
	
	return 200;
}

/*
void menu_option_1() {
	print_lcd_string("Number of tourists in the park:");
	print_lcd_string("Children:");
	char children_count_str[5];
	itoa(num_children_in_park, children_count_str, 10);
	print_lcd_string(children_count_str);
	print_lcd_string("Adults:");
	char adults_count_str[5];
	itoa(num_adults_in_park, adults_count_str, 10);
	print_lcd_string(adults_count_str);
	char total_tourists_count_str[5];
	itoa(num_children_in_park + num_adults_in_park, total_tourists_count_str, 10);
	print_lcd_string("Total:");
	print_lcd_string(total_tourists_count_str);
}*/
// Menu Option 2 - Vehicles Still in the Park
/*
void menu_option_2() {
	print_lcd_string("Vehicles still in the park:");
	for (int i = 0; i < num_vehicles_in_park; i++) {
		print_lcd_string(vehicles_in_park[i].type);
	}
}
// Menu Option 3 - Total Money Collected
void menu_option_3() {
	print_lcd_string("Total money collected:");
	int total_collected = fridge_money_collected + entrance_fee_collected;
	char total_collected_str[10];
	itoa(total_collected, total_collected_str, 10);
	print_lcd_string(total_collected_str);
}
// Menu Option 4 - Number of Drivers
void menu_option_4() {
	print_lcd_string("Number of drivers in the park:");
	char drivers_count_str[5];
	itoa(num_drivers_in_park, drivers_count_str, 10);
	print_lcd_string(drivers_count_str);
}*/
// Function to dispense a bottle of water
int calculate_water_cost(int num_bottles) {
	return num_bottles * WATER_COST;
}

// Function to check if the park is full
int is_park_full() {
	return num_children_in_park + num_adults_in_park >= PARK_CAPACITY;
}

void open_money_slot() {
	// Rotate the money slot motor three times
	for (int i = 0; i < 3; i++) {
		PORTF |= (1 << MONEY_SLOT_MOTOR_PIN);
		_delay_ms(100);
		PORTF &= ~(1 << MONEY_SLOT_MOTOR_PIN);
		_delay_ms(100);
	}
	// Delay for 2 seconds to allow the tourist to insert the money
	_delay_ms(2000);
}

// Function to calculate the cost of the water


void dispense_water() {
	send_lcd_command(0x01);
	send_lcd_command(0x80);
	lcd_print("Water availabLe");
	
	send_lcd_command(0xc0);
	lcd_print("@UGX 1500 a bottle");
	
	send_lcd_command(0x94);
	lcd_print("No. of bottles?");
	
	// Rotate the fridge motor twice
	int num_0f_bots=read_key();
	while(num_0f_bots==200){
		num_0f_bots=read_key();
	}	
	
	char bottles=(char)num_0f_bots;
	
	send_lcd_command(0xd4);
	send_lcd_data(bottles);
	_delay_ms(2000);
	
	int cost=calculate_water_cost(num_0f_bots);
	char price[10];
	sprintf(price, "%d", cost);
	
	send_lcd_command(0x01);
	send_lcd_command(0x80);
	lcd_print("TOTAL: UGX ");
	
	send_lcd_command(0x8b);
	lcd_print(price);
	
	send_lcd_command(0xc0);
	lcd_print("Transact? ");
	
	send_lcd_command(0x94);
	lcd_print("1: Yes, 2:exit ");
	
	int response=read_key();
	while(response==200){
		response=read_key();
	}
	
	char resp=(char)response;
	send_lcd_command(0xd4);
	lcd_print(resp);
	_delay_ms(2000);
	
	if (response==1){
		open_money_slot();
		for (int i = 0; i < num_0f_bots; i++) {
			PORTF |= (1 << FRIDGE_MOTOR_PIN);
			_delay_ms(1000); //2 revolutions for a bottle dispensation
			PORTF &= ~(1 << FRIDGE_MOTOR_PIN);
			_delay_ms(2000);// 2s before another bottle is dispensed
		}
		
		send_lcd_command(0x01);
		send_lcd_command(0x80);
		lcd_print("Come again");
	}else{
		send_lcd_command(0x01);
		send_lcd_command(0x80);
		lcd_print("Sorry transaction");
		
		send_lcd_command(0xc0);
		lcd_print("was not completed,");
		
		send_lcd_command(0x94);
		lcd_print("Please try again!!!");
	}
	
}

// Function to open the money slot



// Function to handle the main menu
/*
void handle_main_menu() {
	// Display the main menu
	print_lcd_string("Main Menu");
	print_lcd_string(MENU_OPTION_1);
	print_lcd_string(MENU_OPTION_2);
	print_lcd_string(MENU_OPTION_3);
	print_lcd_string(MENU_OPTION_4);
	print_lcd_string(MENU_OPTION_5);
	print_lcd_string(MENU_OPTION_6);
	print_lcd_string(MENU_OPTION_7);
	print_lcd_string(MENU_OPTION_8);
	print_lcd_string(MENU_OPTION_9);

	// Get the user's selection
	char selection = read_key();

	// Handle the user's selection
	switch (selection) {
		case '1':
		// Display the number of tourists in the park
		print_lcd_string("Number of tourists in the park:");
		print_lcd_string("Children:");
		char children_count_str[5];
		itoa(num_children_in_park, children_count_str, 10);
		print_lcd_string(children_count_str);
		print_lcd_string("Adults:");
		char adults_count_str[5];
		itoa(num_adults_in_park, adults_count_str, 10);
		print_lcd_string(adults_count_str);
		// Calculate and print the total number of tourists
		char total_tourists_count_str[5];
		itoa(num_children_in_park + num_adults_in_park, total_tourists_count_str, 10);
		print_lcd_string("Total:");
		print_lcd_string(total_tourists_count_str);
		break;


		case '2':
		// Display the vehicles that are still in the park
		print_lcd_string("Vehicles still in the park:");
		for (int i = 0; i < num_vehicles_in_park; i++) {
			print_lcd_string(vehicles_in_park[i].type);
		}
		break;

		case '3':
		// Display the total money collected by the park
		 print_lcd_string("Total money collected:");
		 // Calculate the total money collected
		 int total_collected = fridge_money_collected + entrance_fee_collected;
		 char total_collected_str[10];
		 itoa(total_collected, total_collected_str, 10);
		 print_lcd_string(total_collected_str);
		 break;

		case '4':
		print_lcd_string("Number of drivers in the park:");
		char drivers_count_str[5];
		itoa(num_drivers_in_park, drivers_count_str, 10);
		print_lcd_string(drivers_count_str);
		break;
		case '5':
		// Display the number of bottles in the fridge
		print_lcd_string("Number of bottles in the fridge:");
		// Print the number of bottles in the fridge
		break;

		case '6':
		// Replenish the fridge (you need to implement this)
		break;

		case '7':
		// Login (you need to implement this)
		break;

		case '8':
		// Display the number of cars waiting outside the park
		print_lcd_string("Number of cars waiting outside the park:");
		// You need to implement this
		break;

		case '9':
		// Display whether or not the park is full
		print_lcd_string("Park full?");
		if (is_park_full()) {
			print_lcd_string("Yes");
			} else {
			print_lcd_string("No");
		}
		break;

		default:
		// Invalid selection
		print_lcd_string("Invalid selection");
		break;
	}
}*/

// Function to replenish the fridge
/*
void replenish_fridge() {
	// Prompt the attendant to enter the fridge replenishment password
	print_lcd_string("Enter fridge replenishment password:");

	// Read the password from the keypad
	char password[6];
	for (int i = 0; i < 6; i++) {
		password[i] = read_key();
	}

	// Check if the password is correct
	if (strcmp(password, FRIDGE_REPLENISHMENT_PASSWORD) == 0) {
		// The password is correct
		// Implement the replenishment logic here
		} else {
		// The password is incorrect
		print_lcd_string("Incorrect password");
	}
}
*/

// Function to log in
/*
void login() {
	char stored_username[] = "your_username";  // Replace with your actual username
	char stored_password[] = "your_password";  // Replace with your actual password

	// Prompt the attendant to enter their username and password
	print_lcd_string("Enter username:");

	// Read the username from the keypad
	char username[10];
	for (int i = 0; i < 10; i++) {
		username[i] = read_key();
	}

	print_lcd_string("Enter password:");

	// Read the password from the keypad
	char password[10];
	for (int i = 0; i < 10; i++) {
		password[i] = read_key();
	}

	// Check if the username and password are correct
	if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
		// The username and password are correct
		// Implement the logged-in functionality
		print_lcd_string("Logged in successfully");
		} else {
		// The username and password are incorrect
		print_lcd_string("Incorrect username or password");
	}
}*/


// Function to display the other information requested in the prompt
/*
void display_other_information() {
	// Display the number of cars waiting outside the park
	print_lcd_string("Number of cars waiting outside the park:");
	// Implement this functionality

	// Display whether or not the park is full
	print_lcd_string("Park full?");
	if (is_park_full()) {
		print_lcd_string("Yes");
		} else {
		print_lcd_string("No");
	}
}*/

void registerCar(){
	//to be implemented
}

int main() {
	DDRK = 0X07;
	DDRD = 0XFF; 
	DDRE |=(1<<0)|(1<<1)|(1<<2);
	DDRE &=~(1<<4);
	DDRF =0XFF;
	
	init_lcd();
	
	sei();
	EIMSK |= (1<<INT4);
	EICRB |=(1<<ISC40)|(1<<ISC41);
	
	// Your initialization code here
	
	//print_lcd_string("hey");
	//read_key();
	//dispense_water();
	//open_money_slot();
	//calculate_water_cost(4);
	//is_park_full();
	//login();
	//display_other_information();

	while (1) {
		// Main program loop
		//handle_main_menu();
	}

	return 0;
}


ISR(INT4_vect){
	/*PORTF |=(1<<2); //ALARM GOES OFF
	send_lcd_command(0x01);
	send_lcd_command(0x80);
	lcd_print("Incoming tourist");	
	
	send_lcd_command(0xc0);
	lcd_print(" Vehicle");
	_delay_ms(2000);
	PORTF &=~(1<<2); 
	
	registerCar();*/
	
	dispense_water();
}
