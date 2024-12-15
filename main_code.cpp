// Circuit_code.cpp by Ashan Selvaranjan
// Computes impedance of AC circuits with components in series and/or parallel
// Main code

// Include header file
#include "codes.h"

// Declaration of vector of pointers
std::vector<component*> component_library;
std::vector<component*> components_input;
std::vector<component*> series_components;
std::vector<component*> parallel_components;
std::vector<circuit*> current_circuit;
// Declaration of vector of thread
std::vector<std::thread> threads;
// Constants
double frequency_;
double voltage_;
int component_count{ 0 };
// Template function to return input of any type
template<typename t> t return_input(t input) {
	while (true) {
		if (std::cin >> input) {
			break;
		}
		else {
			std::cout << "Enter a valid value!\n";
			std::cin.clear();
			// Ignores error
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	return input;
}
// Function to create a component
void create_component() {
	char type;
	double k_;
	// Declaration of component trait
	double trait;
	// Declaration of real/ideal decision parameter
	char r_i;
	//	Declaration of stray parameters for real components
	double stray_1;
	double stray_2;
	std::cout << "What type of component do you want to create ?\n(Resisitor[R]/[Capacitor[C]/Inductor[I]/Light dependent resistor[L])" << std::endl;
	type = return_input('a');
	// Instance a resistor is chosen to be created
	if (type == 'R') {
		std::cout << "Is the resistor real or ideal? (r/i)" << std::endl;
		r_i = return_input('a');
		if (r_i == 'r') {
			std::cout << "What is the resistance (in Ohms)?" << std::endl;
			trait = return_input(1.0);
			std::cout << "What is the stray capacitance (in Farads)?" << std::endl;
			stray_1 = return_input(1.0);
			std::cout << "What is the stray inductancce (in Henries)?" << std::endl;
			stray_2 = return_input(1.0);
			// Construct non ideal resistor
			real_resistor* test_r = new real_resistor(trait, stray_1, stray_2);
			test_r->set_freq(frequency_);
			component_library.emplace_back(test_r);
			std::cout << "Component created!" << std::endl;
		}
		if (r_i == 'i') {
			std::cout << "What is the resistance (in Ohms)?" << std::endl;
			trait = return_input(1.0);
			// Construct ideal resistor
			resistor* test_r = new resistor(trait);
			test_r->set_freq(frequency_);
			component_library.emplace_back(test_r);
			std::cout << "Component created!" << std::endl;
		}
	}
	if (type == 'C') {
		std::cout << "Is the capacitor real or ideal? (r/i)" << std::endl;
		r_i = return_input('a');
		if (r_i == 'r') {
			std::cout << "What is the capacitance (in Farads)?" << std::endl;
			trait = return_input(1.0);
			std::cout << "What is the stray resistance (in Ohms)?" << std::endl;
			stray_1 = return_input(1.0);
			std::cout << "What is the stray inductancce (in Henries)?" << std::endl;
			stray_2 = return_input(1.0);
			// Construct non ideal capacitor
			real_capacitor* test_c = new real_capacitor(trait, stray_1, stray_2);
			test_c->set_freq(frequency_);
			component_library.emplace_back(test_c);
			std::cout << "Component created!" << std::endl;
		}
		if (r_i == 'i') {
			std::cout << "What is the capacitance (in Farads)?" << std::endl;
			trait = return_input(1.0);
			// Construct ideal resistor
			capacitor* test_c = new capacitor(trait);
			test_c->set_freq(frequency_);
			component_library.emplace_back(test_c);
			std::cout << "Component created!" << std::endl;
		}
	}
	if (type == 'I') {
		std::cout << "Is the inductor real or ideal? (r/i)" << std::endl;
		r_i = return_input('a');
		if (r_i == 'r') {
			std::cout << "What is the inductance (in Henries)?" << std::endl;
			trait = return_input(1.0);
			std::cout << "What is the stray resistance (in Ohms)?" << std::endl;
			stray_1 = return_input(1.0);
			std::cout << "What is the stray capacitance (in Henries)?" << std::endl;
			stray_2 = return_input(1.0);
			// Construct non ideal inductor
			real_inductor* test_i = new real_inductor(trait, stray_1, stray_2);
			test_i->set_freq(frequency_);
			component_library.emplace_back(test_i);
			std::cout << "Component created!" << std::endl;
		}
		if (r_i == 'i') {
			std::cout << "What is the inductance (in Henries)?" << std::endl;
			trait = return_input(1.0);
			// Construct ideal inductor
			inductor* test_i = new inductor(trait);
			test_i->set_freq(frequency_);
			component_library.emplace_back(test_i);
			std::cout << "Component created!" << std::endl;
		}else {
			std::cout << "Sorry your input was not one of the options! Please try creating a component again." << std::endl;
		}
	}
	if (type == 'L') {
		std::cout << "What is the light intensity (in LUX)?" << std::endl;
		trait = return_input(1.0);
		std::cout << "What is the k constant for the LDR you are creating, where resistance = k/light_intensity is the model" << std::endl;
		k_ = return_input(1.0);
		// Construct light dependent resistor
		light_dependent_resistor* test_ldr = new light_dependent_resistor(trait, k_);
		test_ldr->set_freq(frequency_);
		component_library.emplace_back(test_ldr);
		std::cout << "Component created!" << std::endl;
	}
	component_count += 1;
}
// Printing function
void print_library() {
	std::cout << "Component library:" << std::endl;
	std::cout << "Key - Component" << std::endl;
	if (component_count != 0) {
		
		for (int i = 0; i < component_library.size(); i++) {
			std::cout <<  i << " - ";
			(component_library[i])->details();
		}
	}
}
// Function to utilise threads to print
void print_library_() {
	threads.push_back(std::thread(print_library));
	for (auto& th : threads) {
		th.join();
	}
	threads.clear();
}
// Function to add components in series
void circuit::add_series(std::vector<component*> components_input_) {
	std::string decision{ "y" };
	print_library_();
	// While loop for multiple components
	while (decision == "y") {
		std::cout << "Which component do you want to add in series? (enter key number)\n" << std::endl;
		components_input_.emplace_back(component_library[return_input(0)]);
		std::cout << "Component added!" << std::endl;
		std::cout << "Would you like to add another component (y/n)?";
		std::cin >> decision;
		if (decision == "n") {
			break;
		}
	}	// For loop to calculate impedance in series
		for (int i = 0; i < components_input_.size() ; i++) {
			components_input_[i]->set_freq(frequency_);
			components_input.emplace_back(components_input_[i]);
			// Z_T = Z1 + Z2 + Z...
			impedance_ += components_input_[i]->get_impedance();
			circuit_description_ += components_input_[i]->circuit_description_();
			series_components.emplace_back(components_input_[i]);
		}
		components_input_.clear();
	}
// Function to add components in parallel
void circuit::add_parallel(std::vector<component*> components_input_) {
	std::string decision{ "y" };
	print_library_();
	// While loop for multiple components
	while (decision == "y") {
		std::cout << "Which component do you want to add in parallel?\n" << std::endl;
		components_input_.emplace_back(component_library[return_input(0)]);
		std::cout << "Component added!" << std::endl;
		std::cout << "Would you like to add another component (y/n)?";
		std::cin >> decision;
		if (decision == "n") {
			break;
		}
	}
	std::complex<double> impedance_step(0, 0);
	// For loop to calculate impedance in parallel
	for (int i = 0; i < components_input_.size(); i++) {
		components_input.emplace_back(components_input_[i]);
		components_input_[i]->set_freq(frequency_);
		impedance_step += components_input_[i]->get_impedance();
		parallel_components.emplace_back(components_input_[i]);
	}
	// Z_T = (1/Z1 + 1/Z2)^-1
	impedance_ = pow(pow(impedance_, -1) + pow(impedance_step, -1), -1);
	components_input_.clear();
}
// Menu for user options
void start_menu() {
	// Initial inputs to setup circuit
	std::cout << "What is the power supply in Volts? (V)" << std::endl;
	std::cin >> voltage_;
	std::cout << "What is the frequency in Hertz? (Hz)" << std::endl;
	std::cin >> frequency_;
	// Construct circuit
	circuit* created_circuit = new circuit(voltage_, frequency_);
	current_circuit.emplace_back(created_circuit);
	// Loop continuously
	while (true) {
		// Printing menu
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "| What do you want to do?                           | " << std::endl;
		std::cout << "| enter a - create a component                      | " << std::endl;
		std::cout << "| enter b - print component properties              |" << std::endl;
		std::cout << "| enter	c - add a component in series               | " << std::endl;
		std::cout << "| enter d - add a component in parallel             | " << std::endl;
		std::cout << "| enter	e - print details of circuit                | " << std::endl;
		std::cout << "| enter	f - clear circuit and start a new circuit   | " << std::endl;
		std::cout << "| enter	g - exit                                    | " << std::endl;
		char input;
		// Take valid user input
		input = return_input('a');
		switch (input) {
		// Create a component case
		case 'a':
		// Run create component function
			create_component();
			break;
		// Print component library
		case 'b':
			if (component_count == 0) {
				std::cerr << "Component library is empty, please create some components!" << std::endl;
				break;
			}
			for (int i = 0; i < component_library.size(); i++) {
				std::cout << "	";
				component_library[i]->print(); // Print component details
			}
			break;
		// Add components in series
		case 'c':
		// Check if the user hasn't created any components
			if (component_count == 0) {
				std::cerr << "Component library is empty, please create some components!" << std::endl;
				break;
			}
		// Point current circuit to the add series function
			current_circuit[0]->add_series(components_input);
			break;
		// Add components in parallel
		case 'd':
		// Check components are there for a parallel connection
			if (current_circuit[0]->component_count() == 0) {
				std::cerr << "There must be serially connected components before connecting any components in parallel!" << std::endl;
				break;
			}
			current_circuit[0]->add_parallel(components_input);
			break;
		// Display circuit details and circuit diagram
		case 'e':
		// Check components are there to be printed
			if (component_count == 0) {
				std::cerr << "Circuit currently contains no components!" << std::endl;
				break;
			}
			current_circuit[0]->print();
			break;
		// Create new circuit
		case 'f':
		{	// Clear the component library vector
			component_library.clear();
			// Clear the circuit library
			current_circuit.clear();
			std::cout << "Library cleared! Start crerating a new circuit." << std::endl;
			std::cout << "What is the power supply in Volts? (V)" << std::endl;
			std::cin >> voltage_;
			std::cout << "What is the frequency in Hertz? (Hz)" << std::endl;
			std::cin >> frequency_;
			circuit* created_circuit = new circuit(voltage_, frequency_);
			current_circuit.emplace_back(created_circuit);
			break;
		}
		// Exit the programme
		case 'g':
			exit(0);
			break;
		// Default case when input is not in menu
		default:
			std::cout << "Input does not have an action. Please enter one of the choices listed below" << std::endl;
			break;
		}
	}
}
int main() {
	std::cout << "This programme allows the user to create an analogue circuit from the following components: \n";
	std::cout << "\t -Resistors \n" << "\t -Capacitors \n" << "\t -Inductors \n" << "\t -Light Dependent Resistors \n \n";
	std::cout << "The circuit impedance, as well as other circuit and component properties can be displayed. \n";
	std::cout << "To start creating a circuit, create components and add them in series or parallel. \n \n";
	start_menu();
}