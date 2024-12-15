
#ifndef CODES_H
#define CODES_H
// Standard library headers
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>
#include <string>
#include <thread>

// Abstract base class for components
class component {
public:
	// Default constructor
	component() : impedance_{} {}
	// Destructor
	virtual ~component() { std::cout << "Destroy component" << std::endl; }
	// Pure virtual functions
	virtual double get_freq() const = 0;
	virtual void set_freq(const double f) = 0;
	virtual std::complex<double> get_impedance() const = 0;
	virtual double get_mag() const = 0;
	virtual double get_phase() const = 0;
	virtual char circuit_description_() const = 0;
	virtual void details() const = 0;
	virtual void print() const = 0;

protected:
	std::complex<double> impedance_;
};
// Derived class for resistors
class resistor : public component {
public:
	// Default constructor
	resistor() : component() { resistance_ = 0; voltage_ = 0; }
	// Parameterised constructor
	resistor(const double resistance_in);
	// Destructor
	~resistor() { std::cout << "Destroy resistor" << std::endl; }
	// Override virtual functions
	double get_freq() const { return 0; }
	void set_freq(const double f);
	std::complex<double> get_impedance() const;
	double get_mag() const;
	double get_phase() const;
	char circuit_description_() const { return 'R'; };
	void details() const;
	void print() const;

protected:
	double resistance_{0};
	double voltage_{0};
};
class real_resistor : public resistor {
public:
	//default constructor
	real_resistor() : resistor() { frequency_ = 0; stray_capacitance = 0; stray_inductance = 0; }
	//parameterised constructor
	real_resistor(const double resistance_in, const double Cs_in, const double Ls_in);
	//destructor
	~real_resistor() { std::cout << "Destroy real resistor" << std::endl; }
	//override functions
	double get_freq() const { return frequency_; }
	void set_freq(const double f);
	char circuit_description_() const { return 'R'; };
	void details() const;
	void print() const;
protected:
	double frequency_{0};
	double stray_capacitance{0};
	double stray_inductance{0};
};

// Derived class for capacitors
class capacitor : public component {
public:
	// Default constructor
	capacitor() : component() { capacitance_ = 0; frequency_ = 0; voltage_ = 0; }
	// Parameterised constructor
	capacitor(const double capacitance_in);
	// Destructor
	~capacitor() { std::cout << "Destroy capacitor" << std::endl; }
	// Override virtual functions
	double get_freq() const { return frequency_; }
	void set_freq(const double f);
	std::complex<double> get_impedance() const;
	double get_mag() const;
	double get_phase() const;
	char circuit_description_() const { return 'C'; };
	void details() const;
	void print() const;

protected:
	double capacitance_{0};
	double frequency_{0};
	double voltage_{0};
};
// Derived class for real capacitor
class real_capacitor : public capacitor {
public:
	//default constructor
	real_capacitor() : capacitor() { stray_resistance = 0; stray_inductance = 0; }
	//parameterised constructor
	real_capacitor(const double capacitance_in, const double Rs_in, const double Ls_in);
	//destructor
	~real_capacitor() { std::cout << "Destroy real capacitor" << std::endl; }
	//override functions
	void set_freq(const double f);
	void details() const;
	void print() const;
protected:
	double stray_resistance{0};
	double stray_inductance{0};
};
// Derived class for inductors
class inductor : public component {
public:
	// Default constructor
	inductor() : component() { inductance_ = 0; frequency_ = 0; voltage_ = 0; }
	// Parameterised constructor
	inductor(const double inductance_in);
	// Destructor
	~inductor() { std::cout << "Destroy inductor" << std::endl; }
	// Override virtual functions
	double get_freq() const { return frequency_; }
	void set_freq(const double f);
	std::complex<double> get_impedance() const;
	double get_mag() const;
	double get_phase() const;
	char circuit_description_() const { return 'I'; };
	void details() const;
	void print() const;

protected:
	double inductance_{0};
	double frequency_{0};
	double voltage_{0};
};
// Derived class for real inductors
class real_inductor : public inductor {
public:
	//default constructor
	real_inductor() : inductor() { stray_resistance = 0; stray_capacitance = 0; }
	//parameterised constructor
	real_inductor(const double inductance_in, const double Rs_in, const double Cs_in);
	//destructor
	~real_inductor() { std::cout << "Destroy real inductor" << std::endl; }
	//override functions
	void set_freq(const double f);
	void details() const;
	void print() const;
private:
	double stray_resistance{0};
	double stray_capacitance{0};
};
// Derived class for light dependent resistor
class light_dependent_resistor : public component {
public:
	// Default constructor
	light_dependent_resistor() : component() { light_intensity = 0; resistance_ = 0; k = 0; }
	// Parameterised constructor
	light_dependent_resistor(const double light_intensity, const double k);
	// Destructor
	~light_dependent_resistor() { std::cout << "Destroy resistor" << std::endl; }
	// Override virtual functions
	double get_freq() const { return 0; }
	void set_freq(const double f);
	std::complex<double> get_impedance() const;
	double get_mag() const;
	double get_phase() const;
	char circuit_description_() const { return 'L'; };
	void details() const;
	void print() const;

protected:
	double light_intensity{0};
	double resistance_{0};
	double k{0};
};
// Base class for circuit components
class circuit {
public:
	// Default constructor
	circuit() : voltage_{ 0 }, frequency_{ 0 } {}
	// Parameterised constructor
	circuit(const double voltage_in, const double frequency_in);
	// Destructor
	~circuit() { std::cout << "Destroy circuit" << std::endl; };
	void add_series(std::vector<component*> series_components);
	void add_parallel(std::vector<component*> parallel_components);
	size_t component_count() const;
	void print() const;

protected:
	std::vector<component*> components_input;
	std::vector<component*> series_components;
	std::vector<component*> parallel_components;
	std::complex <double> impedance_;
	double voltage_;
	double frequency_;
	std::string circuit_description_;
};
#endif#pragma once
