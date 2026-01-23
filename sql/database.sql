--creation de la database
CREATE DATABASE IF NOT EXISTS course_supports;
USE course_supports;

-- Creation de la  table support
CREATE TABLE IF NOT EXISTS support (
    id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(255),
    module VARCHAR(100),
    type VARCHAR(50),
    teacher VARCHAR(255),
    path VARCHAR(255),
    date_added VARCHAR(50)
);
