
/*Use the infinity database*/
USE infinity;


/*query 1*/
SELECT Model_ID, Processor_Speed, HDD_Space
FROM Computers
WHERE Price < 500;

/*query 2*/
SELECT DISTINCT Manufacturer_ID FROM Printers;

/*query 3*/
SELECT Model_ID, RAM, ScreenSize
FROM Computers
WHERE isLaptop = 1 AND Price > 1000;

/*query 4*/
SELECT * From Printers
WHERE hasColor = 1;

/*query 5*/
SELECT Model_ID, Processor_Speed, HDD_Space
FROM Computers
WHERE 12 = CD_Speed AND Price < 600 OR  24 = CD_Speed AND Price < 600;

/*query 6*/
SELECT ComputersAndManufacturers.Manufacturer_ID, Computers.Processor_Speed
FROM Computers
INNER JOIN ComputersAndManufacturers ON ComputersAndManufacturers.Computer_ID=Computers.Computer_ID
WHERE Computers.HDD_Space >= 10;

/*query 7*/
SELECT c.Model_ID, c.Price, 'Computer' AS ProductType
FROM Computers c
JOIN ComputersAndManufacturers cam ON cam.Computer_ID=c.Computer_ID AND cam.Manufacturer_ID=2
UNION
SELECT p.Model_ID, p.Price, 'Printer' AS ProductType
FROM Printers p
WHERE p.Model_ID=2;

/*query 8*/
SELECT cam.Manufacturer_ID, sum(c.isLaptop) AS ProductSum
FROM Computers c
JOIN ComputersAndManufacturers cam ON cam.Computer_ID=c.Computer_ID
GROUP BY cam.Manufacturer_ID
HAVING ProductSum=0;

/*query 9*/
SELECT DISTINCT m.Name
FROM Manufacturers m
JOIN ComputersAndManufacturers cam ON cam.Manufacturer_ID=m.Manufacturer_ID
JOIN Computers c ON cam.Computer_ID=c.Computer_ID
WHERE c.Processor_Speed>=450;

/*query 10*/
SELECT pm.Name
FROM PrinterModels pm
JOIN Printers p ON p.Model_ID = pm.Model_ID
WHERE p.Price = (SELECT MAX(Price) FROM Printers);

/*query 11*/
SELECT AVG(c.Processor_Speed) AS AverageSpeed
FROM Computers c;

/*query 12*/
SELECT AVG(c.Processor_Speed) AS AverageSpeed
FROM Computers c
WHERE c.Price>1000;

/*query 13*/
SELECT AVG(c.Processor_Speed) AS AverageSpeed
FROM Computers c
JOIN ComputersAndManufacturers cam ON cam.Computer_ID=c.Computer_ID 
WHERE cam.Manufacturer_ID = 1;

/*query 14*/
SELECT m.Name
FROM Manufacturers m
JOIN ComputersAndManufacturers cam ON cam.Manufacturer_ID = m.Manufacturer_ID
JOIN Computers c ON c.Computer_ID = cam.Computer_ID
GROUP BY m.Name
HAVING COUNT(*) > 1;

/*query 15*/
SELECT c.HDD_Space
FROM Computers c
GROUP BY c.HDD_Space
HAVING COUNT(*) > 1;

/*query 16*/
SELECT c1.Model_ID AS FirstModel, c2.Model_ID AS SecondModel
FROM Computers c1
JOIN Computers c2
WHERE c1.Processor_Speed=c2.Processor_Speed AND c1.RAM=c2.RAM AND c1.Model_ID< c2.Model_ID;

/*query 17*/
SELECT DISTINCT c1.Model_ID
FROM Computers c1
JOIN Computers c2
WHERE c1.isLaptop=1 AND c2.isLaptop=0 AND c1.Processor_Speed<(SELECT MIN(Processor_Speed) FROM Computers c WHERE c.isLaptop=0);

/*query 18*/
SELECT m.Name, p.Price
FROM Printers p
JOIN Manufacturers m
WHERE m.Manufacturer_ID=p.Manufacturer_ID AND p.Price=(SELECT MIN(Price) FROM Printers p);

/*query 19*/
SELECT DISTINCT m.Name, AVG(c.ScreenSize) AS AverageScreenSize
FROM Manufacturers m
JOIN ComputersAndManufacturers cam ON cam.Manufacturer_ID=m.Manufacturer_ID
JOIN Computers c ON c.Computer_ID=cam.Computer_ID
WHERE c.isLaptop=1
GROUP BY c.Model_ID, m.Name;

/*query 20*/
SELECT DISTINCT m.Name
FROM Manufacturers m
JOIN ComputersAndManufacturers cam ON cam.Manufacturer_ID=m.Manufacturer_ID
JOIN Computers c ON c.Computer_ID=cam.Computer_ID
WHERE c.Model_ID IN (
	SELECT c.Model_ID
	FROM Computers c
	GROUP BY c.Model_ID
	HAVING COUNT(*) > 3
);

/*query 21*/
SELECT m.Name, MAX(Price)
FROM Manufacturers m
JOIN ComputersAndManufacturers cam ON cam.Manufacturer_ID=m.Manufacturer_ID
JOIN Computers c ON c.Computer_ID=cam.Computer_ID
GROUP BY m.Name;

/*query 22*/
SELECT c.Processor_Speed, AVG(c.Price) AS AveragePrice
FROM Computers c
WHERE c.Processor_Speed>600
GROUP BY c.Processor_Speed;

/*query 23*/
SELECT m.Name
FROM Manufacturers m
JOIN ComputersAndManufacturers cam ON m.Manufacturer_ID = cam.Manufacturer_ID
JOIN Computers c ON cam.Computer_ID = c.Computer_ID
WHERE c.Processor_Speed >= 750
GROUP BY m.Name
HAVING SUM(c.isLaptop = 1) > 0 AND SUM(c.isLaptop = 0) > 0;

/*query 24*/
SELECT DISTINCT m.Manufacturer_ID AS ManufacturersWithPrintersAndMinRAM
FROM Manufacturers m
WHERE m.Manufacturer_ID IN (
	SELECT DISTINCT m.Manufacturer_ID
	FROM Manufacturers m
	JOIN Printers p ON p.Manufacturer_ID=m.Manufacturer_ID
) AND m.Manufacturer_ID IN (
	SELECT DISTINCT m.Manufacturer_ID
	FROM Manufacturers m
	JOIN ComputersAndManufacturers cam ON cam.Manufacturer_ID=m.Manufacturer_ID 
	JOIN Computers c ON c.Computer_ID=cam.Computer_ID
	WHERE c.Processor_Speed = (SELECT MAX(Processor_Speed) 
		FROM Computers c
		WHERE c.Computer_ID IN (
			SELECT c.Computer_ID
			FROM Computers c
			WHERE c.RAM = (SELECT MIN(RAM) FROM Computers s)
		)
	)
);

/*query 25*/
SELECT AVG(c.Price) AS AveragePriceOfManufacturerA
FROM Computers c
JOIN ComputersAndManufacturers cam ON cam.Computer_ID = c.Computer_ID
JOIN Manufacturers m ON cam.Manufacturer_ID = m.Manufacturer_ID
WHERE m.Manufacturer_ID = 1;

SELECT DISTINCT m.Manufacturer_ID AS hey
FROM Manufacturers m
JOIN Printers p ON p.Manufacturer_ID=m.Manufacturer_ID;

/*query 26*/
SELECT m.Name, AVG(c.HDD_Space) AS Average_HDD_Space
FROM Manufacturers m
JOIN ComputersAndManufacturers cam ON cam.Manufacturer_ID = m.Manufacturer_ID
JOIN Computers c ON cam.Computer_ID = c.Computer_ID
WHERE m.Manufacturer_ID IN (
	SELECT DISTINCT m.Manufacturer_ID
	FROM Manufacturers m
	JOIN Printers p ON p.Manufacturer_ID=m.Manufacturer_ID
)
GROUP BY m.Name;

/*query 27*/
INSERT INTO ComputerModels (Model_ID, Name)
SELECT DISTINCT Model_ID + 1000, concat('Laptop Group ', Model_ID + 1000)
FROM Computers
WHERE isLaptop = 1
AND (Model_ID + 1000) NOT IN(SELECT Model_ID FROM ComputerModels);

INSERT INTO Computers (Computer_ID, Model_ID, RAM, HDD_Space, Processor_Speed, ScreenSize, isLaptop, Price)
SELECT MIN(Computer_ID) + 20, Model_ID + 1000, MAX(RAM) * 2, MAX(HDD_Space) * 2, MAX(Processor_Speed), NULL, 1, MAX(Price) / 1.5
FROM Computers 
WHERE isLaptop = 1
GROUP BY Model_ID;

/*query 28*/
/*Delete from ComputersAndManufacturers*/
DELETE FROM ComputersAndManufacturers
WHERE Computer_ID IN (
    SELECT Computer_ID
    FROM (
        SELECT c.Computer_ID
        FROM Computers c
        WHERE c.RAM = (SELECT MIN(RAM) FROM Computers)
           OR c.HDD_Space = (SELECT MIN(HDD_Space) FROM Computers)
    ) AS temp
);

/*Now delete from Computers*/
DELETE FROM Computers
WHERE Computer_ID IN (
    SELECT Computer_ID
    FROM (
        SELECT c.Computer_ID
        FROM Computers c
        WHERE c.RAM = (SELECT MIN(RAM) FROM Computers)
           OR c.HDD_Space = (SELECT MIN(HDD_Space) FROM Computers)
    ) AS temp
);



