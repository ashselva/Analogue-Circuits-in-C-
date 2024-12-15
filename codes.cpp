// Include header file
#include "codes.h"
// Declare constant value for pi
const double pi = acos(-1.0);
// Component class member functions
// Parameterised constructors
resistor::resistor(const double resistance_input) {
	resistance_ = resistance_input;
	// Impedance, Z = R
	impedance_ = resistance_;
}
capacitor::capacitor(const double capacitance_input) {;
	capacitance_ = capacitance_input;
}
inductor::inductor(const double inductance_input) {
	inductance_ = inductance_input;
}
light_dependent_resistor::light_dependent_resistor(const double light_intensity_input, const double k_input) {
	resistance_ = k_input / light_intensity_input;
	impedance_ = resistance_;
}
real_resistor::real_resistor(const double resistance_in, const double Cs_in, const double Ls_in) : resistor(resistance_in) {
	stray_capacitance = Cs_in;
	stray_inductance = Ls_in;
}
real_capacitor::real_capacitor(const double capacitance_in, const double Rp_in, const double Lp_in) : capacitor(capacitance_in) {
	stray_resistance = Rp_in;
	stray_inductance = Lp_in;
}
real_inductor::real_inductor(const double inductance_in, const double Rp_in, const double Cp_in) : inductor(inductance_in) {
	stray_resistance = Rp_in;
	stray_capacitance = Cp_in;
}
// Set frequency functions
void resistor::set_freq(const double f) {
	// Nothing as Z = R
}
void capacitor::set_freq(const double f) {
	frequency_ = 2 * pi * f; //w = 2pi*f
	// Set impedance
	std::complex<double> Z(0, -1 / (frequency_ * capacitance_)); //Z = -i/wC
	impedance_ = Z;
}
void inductor::set_freq(const double f) {
	frequency_ = 2 * pi * f; //w = 2pi*f
	// Set impedance
	std::complex<double> Z(0, frequency_ * inductance_); //Z = 2*pi*wL	
	impedance_ = Z;
}
void light_dependent_resistor::set_freq(const double f) {
}
void real_resistor::set_freq(const double f) {
	frequency_ = 2 * pi * f; //w =2pi*f
	// Set impedance
	std::complex<double> numerator;
	numerator = resistance_ + (frequency_ * stray_inductance);
	std::complex<double> denominator;
	denominator = (1 - pow(frequency_, 2) * stray_capacitance * stray_inductance) + (frequency_ * resistance_ * stray_capacitance);
	// Z = R + iwLs / (1 - w^2CsLs) + iwRCs
	std::complex<double> Z = numerator / denominator;
	impedance_ = Z;
}
void real_capacitor::set_freq(const double f) {
	frequency_ = 2 * pi * f; //w =2pi*f
	// Set impedance
	std::complex<double> Z(stray_resistance, frequency_ * stray_inductance - 1 / (frequency_ * capacitance_)); // Z = Rs + i(wLs - 1/wC)
	impedance_ = Z;
}
void real_inductor::set_freq(const double f) {
	// w = 2pi * f
	frequency_ = 2 * pi * f;
	// Set impedance
	std::complex<double> numerator(stray_resistance, frequency_ * inductance_);
	std::complex<double> denominator(1 - frequency_ * frequency_ * stray_capacitance * inductance_, frequency_ * stray_resistance * stray_capacitance);
	std::complex<double> Z = numerator / denominator; //Z = Rs + iwL / (1 - w^2CsL) + iwRsCs
	impedance_ = Z;
}
// Get impedance functions
std::complex<double> resistor::get_impedance() const {
	return impedance_;
}
std::complex<double> capacitor::get_impedance() const {
	return impedance_;
}
std::complex<double> inductor::get_impedance() const {
	return impedance_;
}
std::complex<double> light_dependent_resistor::get_impedance() const {
	return impedance_;
}
// Get magnitude functions
double resistor::get_mag() const {
	return abs(impedance_);
}
double capacitor::get_mag() const {
	return abs(impedance_);
}
double inductor::get_mag() const {
	return abs(impedance_);
}
double light_dependent_resistor::get_mag() const {
	return abs(impedance_);
}
// Get phase functions
double resistor::get_phase() const {
	return arg(impedance_); //arg(Z)
}
double capacitor::get_phase() const {
	return arg(impedance_);
}
double inductor::get_phase() const {
	return arg(impedance_);
}
double light_dependent_resistor::get_phase() const {
	return arg(impedance_);
}
// Details functions to display components trait
void resistor::details() const {
	std::cout << resistance_ << " Ohm-Resistor" << std::endl;
}
void capacitor::details() const {
	std::cout << capacitance_ << "F-Capacitor" << std::endl;
}
void inductor::details() const {
	std::cout << inductance_ << "H-Inductor" << std::endl;
}
void light_dependent_resistor::details() const {
	std::cout << resistance_ << " Ohm-Light dependent resistor" << std::endl;
}
void real_resistor::details() const {
	std::cout << resistance_ << " Ohm-Resistor with " << stray_capacitance << "F and " << stray_inductance << "H stray effects" << std::endl;
}
void real_capacitor::details() const {
	std::cout << capacitance_ << "F-Capacitor with " << stray_resistance << " Ohm and " << stray_inductance << "H stray effects" << std::endl;
}
void real_inductor::details() const {
	std::cout << inductance_ << "H-Inductor with " << stray_resistance << " Ohm and " << stray_capacitance << "F stray effects" << std::endl;
}
// Print functions for each component (prints details and impedance)
void resistor::print() const {
	// Print resistor details
	details();
	std::cout << "	Impedance:" << std::endl;
	std::cout << "		-Magnitude: " << get_mag() << " Ohms" << std::endl;
	std::cout << "		-Phase shift: " << get_phase() << " rads" << std::endl;
}
void capacitor::print() const {
	// Print capacitor details
	details();
	std::cout << "	Impedance:" << std::endl;
	std::cout << "		-Magnitude: " << get_mag() << " Ohms" << std::endl;
	std::cout << "		-Phase shift: " << get_phase() << " rads" << std::endl;
}
void inductor::print() const {
	// Print inductor details
	details();
	std::cout << "	Impedance:" << std::endl;
	std::cout << "		-Magnitude: " << get_mag() << " Ohms" << std::endl;
	std::cout << "		-Phase shift: " << get_phase() << " rads" << std::endl;
}
void light_dependent_resistor::print() const {
	// Print light dependent resistor details
	details();
	std::cout << "	Impedance:" << std::endl;
	std::cout << "		-Magnitude: " << get_mag() << " Ohms" << std::endl;
	std::cout << "		-Phase shift: " << get_phase() << " rads" << std::endl;
}
void real_resistor::print() const {
	// Print real resistor details
	details();
	std::cout << "	Impedance:" << std::endl;
	std::cout << "		-Magnitude: " << get_mag() << " Ohms" << std::endl;
	std::cout << "		-Phase shift: " << get_phase() << " rads" << std::endl;
}
void real_capacitor::print() const {
	// Print real capacitor details
	details();
	std::cout << "	Impedance:" << std::endl;
	std::cout << "		-Magnitude: " << get_mag() << " Ohms" << std::endl;
	std::cout << "		-Phase shift: " << get_phase() << " rads" << std::endl;
}
void real_inductor::print() const {
	// Print real inductor details
	details();
	std::cout << "	Impedance:" << std::endl;
	std::cout << "		Magnitude: " << get_mag() << " Ohms" << std::endl;
	std::cout << "		Phase shift: " << get_phase() << " rads" << std::endl;
}
// Circuit class member functions
// Parameterised constructor
circuit::circuit(const double voltage_in, const double frequency_in) {
	// Set v and f
	voltage_ = voltage_in;
	frequency_ = frequency_in;
	// Initialise text description as blank
	circuit_description_ = "";
}
// Function to return no of components
size_t circuit::component_count() const {
	// Length of components input vector
	return components_input.size();
}
// Member function to print circuit details and diagram
void circuit::print() const {
	std::cout << "Circuit:" << std::endl;
	std::cout << "	-Frequency: " << frequency_ << "Hz" << std::endl;
	std::cout << "	-Voltage = " << voltage_ << "V" << std::endl;
	std::cout << "	-Current = " << voltage_ / abs(impedance_) << "A" << std::endl;
	// Print circuit impedance
	std::cout << " Circuit impedance:" << std::endl;
	std::cout << "\t -Impedance =  " << impedance_ << std::endl;
	std::cout << "	-Magnitude = " << abs(impedance_) << " Ohms" << std::endl;
	std::cout << "	-Phase shift = " << arg(impedance_) << " rads" << std::endl;
	// Print circuit component information
	std::cout << " Circuit components: \n\n";
	for (int i = 0; i < components_input.size(); i++) {
		std::cout << "	";
		components_input[i]->print();
		}
	// Print circuit diagram
	std::cout << "Circuit diagram:" << std::endl;
	if (series_components.size() != 0) {
		std::cout << "-------------V--------------" << std::endl;
		std::cout << "|                          |" << std::endl;
		// Loop for series components
		for (int i = 0; i < series_components.size(); i++) {
			// If statements for specific number of components in circuit
			if (series_components.size() == 1) {
				std::cout << "-------------" << series_components[i]->circuit_description_() << "-------------";
			}
			if (series_components.size() == 2) {
				std::cout << "------" << series_components[i]->circuit_description_() << "-------";
			}
			if (series_components.size() == 3) {
				std::cout << "----" << series_components[i]->circuit_description_() << "----";
			}
			if (series_components.size() == 4) {
				std::cout << "---" << series_components[i]->circuit_description_() << "---";
			}
			if (series_components.size() == 5) {
				std::cout << "--" << series_components[i]->circuit_description_() << "--";
			}
			if (series_components.size() == 6) {
				std::cout << "-" << series_components[i]->circuit_description_() << "--";
			}
		}
	}
	else {
		std::cout << "There are no components in the circuit, add components before viewing circuit." << std::endl;
	}
	// Loop for parallel components
	for (int i = 0; i < parallel_components.size(); i++) {
			std::cout << "\n|\n" << "-------------" << parallel_components[i]->circuit_description_() << "-------------" << "|";
		}
}	
