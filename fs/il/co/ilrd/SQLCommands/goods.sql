
/*Use the infinity database*/
USE infinity;

/***** Enter goods to tables *****/

/* Add new manufacturers */
INSERT INTO Manufacturers (Name)
VALUES ('Intel');

INSERT INTO Manufacturers (Name)
VALUES ('Sony');

INSERT INTO Manufacturers (Name)
VALUES ('Apple');

INSERT INTO Manufacturers (Name)
VALUES ('Dell');

INSERT INTO Manufacturers (Name)
VALUES ('Asus');


/* Add new computer models */
INSERT INTO ComputerModels (Name)
VALUES ('NUC');

INSERT INTO ComputerModels (Name)
VALUES ('Macbook');

INSERT INTO ComputerModels (Name)
VALUES ('Playstation');

INSERT INTO ComputerModels (Name)
VALUES ('Vostro');


/* Add new computers*/
INSERT INTO Computers (Computer_ID, Model_ID, RAM, HDD_Space, Processor_Speed, ScreenSize, isLaptop, Price)
VALUES (1, 1, 32, 1024, 4203, 15, 1, 1201);

INSERT INTO Computers (Computer_ID, Model_ID, RAM, HDD_Space, Processor_Speed, ScreenSize, isLaptop, Price)
VALUES (2, 1, 16, 1024, 4202, 15, 1, 1101);

INSERT INTO Computers (Computer_ID, Model_ID, RAM, HDD_Space, Processor_Speed, ScreenSize, isLaptop, Price)
VALUES (3, 2, 32, 9, 4203, 15, 1, 401);

INSERT INTO Computers (Computer_ID, Model_ID, RAM, CD_Speed, HDD_Space, Processor_Speed, isLaptop, Price)
VALUES (4, 2, 32, 12, 516, 3601, 0, 410);

INSERT INTO Computers (Computer_ID, Model_ID, RAM, CD_Speed, HDD_Space, Processor_Speed, isLaptop, Price)
VALUES (5, 2, 16, 24, 516, 3602, 0, 420);

INSERT INTO Computers (Computer_ID, Model_ID, RAM, CD_Speed, HDD_Space, Processor_Speed, isLaptop, Price)
VALUES (6, 2, 8, 12, 6, 3603, 0, 630);

INSERT INTO Computers (Computer_ID, Model_ID, RAM, HDD_Space, Processor_Speed, ScreenSize, isLaptop, Price)
VALUES (7, 3, 8, 5, 4204, 15, 1, 510);

INSERT INTO Computers (Computer_ID, Model_ID, RAM, HDD_Space, Processor_Speed, ScreenSize, isLaptop, Price)
VALUES (8, 3, 16, 2048, 4600, 15, 1, 520);

INSERT INTO Computers (Computer_ID, Model_ID, RAM, HDD_Space, Processor_Speed, ScreenSize, isLaptop, Price)
VALUES (9, 4, 32, 516, 16, 14, 1, 530);

INSERT INTO Computers (Computer_ID, Model_ID, RAM, CD_Speed, HDD_Space, Processor_Speed, isLaptop, Price)
VALUES (10, 2, 32, 12, 7, 17, 0, 640);

INSERT INTO Computers (Computer_ID, Model_ID, RAM, CD_Speed, HDD_Space, Processor_Speed, isLaptop, Price)
VALUES (11, 2, 16, 24, 9, 3605, 0, 450);

INSERT INTO Computers (Computer_ID, Model_ID, RAM, CD_Speed, HDD_Space, Processor_Speed, isLaptop, Price)
VALUES (12, 2, 8, 12, 1024, 3606, 0, 460);


/* Add new computer and manufacturers */
INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (1, 1);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (1, 2);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (1, 4);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (2, 1);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (2, 4);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (3, 1);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (4, 2);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (4, 4);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (4, 3);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (5, 3);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (6, 3);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (7, 1);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (8, 2);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (9, 4);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (7, 4);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (8, 1);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (9, 1);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (10, 3);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (11, 3);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (12, 3);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (10, 1);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (11, 2);

INSERT INTO ComputersAndManufacturers (Computer_ID, Manufacturer_ID)
VALUES (12, 4);


/* Add PrinterModels */
INSERT INTO PrinterModels (Name)
VALUES ('EcoTank');

INSERT INTO PrinterModels (Name)
VALUES ('OfficeJet');

INSERT INTO PrinterModels (Name)
VALUES ('PriFix');


/* Add Printers */
INSERT INTO Printers (Manufacturer_ID, Model_ID, hasColor, Price)
VALUES (1, 1, 1, 200);

INSERT INTO Printers (Manufacturer_ID, Model_ID, hasColor, Price)
VALUES (2, 1, 0, 150);

INSERT INTO Printers (Manufacturer_ID, Model_ID, hasColor, Price)
VALUES (3, 3, 0, 160);

INSERT INTO Printers (Manufacturer_ID, Model_ID, hasColor, Price)
VALUES (2, 2, 1, 220);


/* Display tables for visualization*/
SELECT * FROM Manufacturers;
SELECT * FROM ComputerModels;
SELECT * FROM Computers;
SELECT * FROM ComputersAndManufacturers;


