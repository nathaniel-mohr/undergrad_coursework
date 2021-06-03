-- 1.
CREATE TABLE DEPT_STATS(
    `Dnumber` int(2) NOT NULL,
    `Emp_count` int(11) NOT NULL,
    `Avg_salary` decimal(10,2) NOT NULL,
    PRIMARY KEY (`Dnumber`)
);

-- 2.
DELIMITER $$
CREATE PROCEDURE InitDeptStats ()
BEGIN
    INSERT INTO DEPT_STATS
    SELECT Dno, COUNT(SSn) "Number of Employees", AVG(Salary) "Average Salary"
    FROM EMPLOYEE
    GROUP BY Dno;
END $$

CALL `InitDeptStats`();

-- 3.
DELIMITER $$
CREATE TRIGGER `DELETEDept_Stats` AFTER DELETE ON `EMPLOYEE`
 FOR EACH ROW BEGIN
    IF OLD.Dno IS NOT NULL THEN
        UPDATE DEPT_STATS
        SET Avg_salary = (Avg_salary * Emp_count - OLD.Salary) / (Emp_count - 1)
        WHERE DEPT_STATS.Dnumber = OLD.Dno;
        UPDATE DEPT_STATS
        SET Emp_count = Emp_count - 1
        WHERE DEPT_STATS.Dnumber = OLD.Dno;
    END IF;
END $$


DELIMITER $$
CREATE TRIGGER `INSERTDept_Stats` AFTER INSERT ON `EMPLOYEE`
 FOR EACH ROW BEGIN
    IF NEW.Dno IS NOT NULL THEN
        UPDATE DEPT_STATS
        SET Emp_count = Emp_count + 1
        WHERE DEPT_STATS.Dnumber = NEW.Dno;
        UPDATE DEPT_STATS
        SET Avg_salary = Avg_salary + (NEW.salary - Avg_salary) / Emp_count
        WHERE DEPT_STATS.Dnumber = NEW.Dno;
    END IF;
END $$

DELIMITER $$
CREATE TRIGGER `UPDATEDept_Stats` AFTER UPDATE ON `EMPLOYEE`
 FOR EACH ROW BEGIN
    IF OLD.Dno IS NOT NULL THEN
        UPDATE DEPT_STATS
        SET Avg_salary = (Avg_salary * Emp_count - OLD.Salary) / (Emp_count - 1)
        WHERE DEPT_STATS.Dnumber = OLD.Dno;
        UPDATE DEPT_STATS
        SET Emp_count = Emp_count - 1
        WHERE DEPT_STATS.Dnumber = OLD.Dno;
    END IF;

    IF NEW.Dno IS NOT NULL THEN
        UPDATE DEPT_STATS
        SET Emp_count = Emp_count + 1
        WHERE DEPT_STATS.Dnumber = NEW.Dno;
        UPDATE DEPT_STATS
        SET Avg_salary = Avg_salary + (NEW.salary - Avg_salary) / Emp_count
        WHERE DEPT_STATS.Dnumber = NEW.Dno;
    END IF;
END $$


-- 4.
DELIMITER $$
CREATE TRIGGER `MaxTotalHours` 
BEFORE INSERT ON WORKS_ON 
FOR EACH ROW
BEGIN 
	DECLARE total decimal(3,1);
    DECLARE message varchar(100);
    
    SELECT SUM(Hours) INTO total FROM WORKS_ON WHERE NEW.Essn = Essn;
    
    SET message = concat("You entered ", NEW.Hours, ". You currrently work ", total, ". You are over 40.0 hours.");
    SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT=message;    

END; $$

-- 5.
DELIMITER $$
CREATE FUNCTION PayLevel(empSsn INT)
RETURNS VARCHAR(100)
BEGIN
	DECLARE amount decimal(10,2);
    DECLARE sal decimal(10,2);
    DECLARE dep int(2);
    
    SELECT Dno INTO dep FROM EMPLOYEE WHERE empSsn = Ssn;
    
    SELECT Salary INTO sal FROM EMPLOYEE WHERE Ssn=empSsn;
    
    SELECT AVG(Salary) INTO amount FROM EMPLOYEE
    WHERE Dno = dep
    GROUP BY Dno;
    	
	RETURN (CASE 
    	WHEN sal > amount THEN "Above Average"
        WHEN sal = amount THEN "Average"
        WHEN sal < amount THEN "Below Average"
        ELSE "ERROR"
		END);
END
$$