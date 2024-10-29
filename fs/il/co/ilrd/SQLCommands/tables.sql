
/*create database*/
CREATE DATABASE infinity;

/*Use the infinity database*/
USE infinity;

/*****Creating Manufacturers table*****/
CREATE TABLE Manufacturers (
	Manufacturer_ID INT PRIMARY KEY AUTO_INCREMENT,
	Name VARCHAR(20)
);

/*****Creating the computer related tables*****/
CREATE TABLE ComputerModels (
	Model_ID INT PRIMARY KEY AUTO_INCREMENT,
	Name VARCHAR(20)
);

CREATE TABLE Computers (
	Computer_ID INT PRIMARY KEY,
	Model_ID INT NOT NULL,
	RAM INT NOT NULL,
	CD_Speed INT,
	HDD_Space INT NOT NULL,
	Processor_Speed INT NOT NULL,
	ScreenSize INT,
	isLaptop TINYINT(1),
	Price INT,
	FOREIGN KEY (Model_ID) REFERENCES ComputerModels(Model_ID)
);

CREATE TABLE ComputersAndManufacturers (
	Computer_ID INT,
	Manufacturer_ID INT,
	PRIMARY KEY (Computer_ID, Manufacturer_ID),
	FOREIGN KEY (Computer_ID) REFERENCES Computers(Computer_ID),
	FOREIGN KEY (Manufacturer_ID) REFERENCES Manufacturers(Manufacturer_ID)
);

/*****Creating the printer related tables*****/
CREATE TABLE PrinterModels (
	Model_ID INT PRIMARY KEY AUTO_INCREMENT,
	Name VARCHAR(20) NOT NULL
);

CREATE TABLE Printers (
	Printer_ID INT PRIMARY KEY AUTO_INCREMENT,
	Manufacturer_ID INT,
	Model_ID INT NOT NULL,
	hasColor TINYINT(1),
	Price INT,
	FOREIGN KEY (Manufacturer_ID) REFERENCES Manufacturers(Manufacturer_ID),
	FOREIGN KEY (Model_ID) REFERENCES PrinterModels(Model_ID)
);


