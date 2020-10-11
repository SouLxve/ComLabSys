-- MySQL dump 10.13  Distrib 8.0.21, for Win64 (x86_64)
--
-- Host: localhost    Database: test
-- ------------------------------------------------------
-- Server version	8.0.21

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `date_info`
--

DROP TABLE IF EXISTS `date_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `date_info` (
  `date_id` int NOT NULL AUTO_INCREMENT,
  `date_str` varchar(10) NOT NULL,
  PRIMARY KEY (`date_id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `date_info`
--

LOCK TABLES `date_info` WRITE;
/*!40000 ALTER TABLE `date_info` DISABLE KEYS */;
INSERT INTO `date_info` VALUES (1,'周一'),(2,'周二'),(3,'周三'),(4,'周四'),(5,'周五'),(6,'周六'),(7,'周日');
/*!40000 ALTER TABLE `date_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `friday_room_margin`
--

DROP TABLE IF EXISTS `friday_room_margin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `friday_room_margin` (
  `room_id` int NOT NULL,
  `room_margin_1` int NOT NULL,
  `room_margin_2` int NOT NULL,
  `room_margin_3` int NOT NULL,
  `room_margin_4` int NOT NULL,
  `room_margin_5` int NOT NULL,
  `week` int NOT NULL,
  KEY `room_id` (`room_id`),
  CONSTRAINT `friday_room_margin_ibfk_1` FOREIGN KEY (`room_id`) REFERENCES `room_info` (`room_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `friday_room_margin`
--

LOCK TABLES `friday_room_margin` WRITE;
/*!40000 ALTER TABLE `friday_room_margin` DISABLE KEYS */;
INSERT INTO `friday_room_margin` VALUES (1,20,20,20,20,20,1),(1,20,20,20,20,20,2),(1,20,20,20,20,20,3),(1,20,20,20,20,20,4),(1,20,20,20,20,20,5),(1,20,20,20,20,20,6),(1,20,20,20,20,20,7),(1,20,20,20,20,20,8),(1,20,20,20,20,20,9),(1,20,20,20,20,20,10),(1,20,20,20,20,20,11),(1,20,20,20,20,20,12),(1,20,20,20,20,20,13),(1,20,20,20,20,20,14),(1,20,20,20,20,20,15),(1,20,20,20,20,20,16),(1,20,20,20,20,20,17),(1,20,20,20,20,20,18),(2,30,30,30,30,30,1),(2,30,30,30,30,30,2),(2,30,30,30,30,30,3),(2,30,30,30,30,30,4),(2,30,30,30,30,30,5),(2,30,30,30,30,30,6),(2,30,30,30,30,30,7),(2,30,30,30,30,30,8),(2,30,30,30,30,30,9),(2,30,30,30,30,30,10),(2,30,30,30,30,30,11),(2,30,30,30,30,30,12),(2,30,30,30,30,30,13),(2,30,30,30,30,30,14),(2,30,30,30,30,30,15),(2,30,30,30,30,30,16),(2,30,30,30,30,30,17),(2,30,30,30,30,30,18),(3,40,40,40,40,40,1),(3,40,40,40,40,40,2),(3,40,40,40,40,40,3),(3,40,40,40,40,40,4),(3,40,40,40,40,40,5),(3,40,40,40,40,40,6),(3,40,40,40,40,40,7),(3,40,40,40,40,40,8),(3,40,40,40,40,40,9),(3,40,40,40,40,40,10),(3,40,40,40,40,40,11),(3,40,40,40,40,40,12),(3,40,40,40,40,40,13),(3,40,40,40,40,40,14),(3,40,40,40,40,40,15),(3,40,40,40,40,40,16),(3,40,40,40,40,40,17),(3,40,40,40,40,40,18),(8,40,40,40,40,40,1),(8,40,40,40,40,40,2),(8,40,40,40,40,40,3),(8,40,40,40,40,40,4),(8,40,40,40,40,40,5),(8,40,40,40,40,40,6),(8,40,40,40,40,40,7),(8,40,40,40,40,40,8),(8,40,40,40,40,40,9),(8,40,40,40,40,40,10),(8,40,40,40,40,40,11),(8,40,40,40,40,40,12),(8,40,40,40,40,40,13),(8,40,40,40,40,40,14),(8,40,40,40,40,40,15),(8,40,40,40,40,40,16),(8,40,40,40,40,40,17),(8,40,40,40,40,40,18);
/*!40000 ALTER TABLE `friday_room_margin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `monday_room_margin`
--

DROP TABLE IF EXISTS `monday_room_margin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `monday_room_margin` (
  `room_id` int NOT NULL,
  `room_margin_1` int NOT NULL,
  `room_margin_2` int NOT NULL,
  `room_margin_3` int NOT NULL,
  `room_margin_4` int NOT NULL,
  `room_margin_5` int NOT NULL,
  `week` int NOT NULL,
  KEY `room_id` (`room_id`),
  CONSTRAINT `monday_room_margin_ibfk_1` FOREIGN KEY (`room_id`) REFERENCES `room_info` (`room_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `monday_room_margin`
--

LOCK TABLES `monday_room_margin` WRITE;
/*!40000 ALTER TABLE `monday_room_margin` DISABLE KEYS */;
INSERT INTO `monday_room_margin` VALUES (1,20,20,20,20,20,1),(1,20,20,20,20,20,2),(1,20,20,20,20,20,3),(1,20,20,20,20,20,4),(1,20,20,20,20,20,5),(1,20,20,20,20,20,6),(1,20,20,20,20,20,7),(1,20,20,20,20,20,8),(1,20,20,20,20,20,9),(1,20,20,20,20,20,10),(1,20,20,20,20,20,11),(1,20,20,20,20,20,12),(1,20,20,20,20,20,13),(1,20,20,20,20,20,14),(1,20,20,20,20,20,15),(1,20,20,20,20,20,16),(1,20,20,20,20,20,17),(1,20,20,20,20,20,18),(2,30,30,30,30,30,1),(2,30,30,30,30,30,2),(2,30,30,30,30,30,3),(2,30,30,30,30,30,4),(2,30,30,30,30,30,5),(2,30,30,30,30,30,6),(2,30,30,30,30,30,7),(2,30,30,30,30,30,8),(2,30,30,30,30,30,9),(2,30,30,30,30,30,10),(2,30,30,30,30,30,11),(2,30,30,30,30,30,12),(2,30,30,30,30,30,13),(2,30,30,30,30,30,14),(2,30,30,30,30,30,15),(2,30,30,30,30,30,16),(2,30,30,30,30,30,17),(2,30,30,30,30,30,18),(3,40,40,40,40,40,1),(3,40,40,40,40,40,2),(3,40,40,40,40,40,3),(3,40,40,40,40,40,4),(3,40,40,40,40,40,5),(3,40,40,40,40,40,6),(3,40,40,40,40,40,7),(3,40,40,40,40,40,8),(3,40,40,40,40,40,9),(3,40,40,40,40,40,10),(3,40,40,40,40,40,11),(3,40,40,40,40,40,12),(3,40,40,40,40,40,13),(3,40,40,40,40,40,14),(3,40,40,40,40,40,15),(3,40,40,40,40,40,16),(3,40,40,40,40,40,17),(3,40,40,40,40,40,18),(8,40,40,40,40,40,1),(8,40,40,40,40,40,2),(8,40,40,40,40,40,3),(8,40,40,40,40,40,4),(8,40,40,40,40,40,5),(8,40,40,40,40,40,6),(8,40,40,40,40,40,7),(8,40,40,40,40,40,8),(8,40,40,40,40,40,9),(8,40,40,40,40,40,10),(8,40,40,40,40,40,11),(8,40,40,40,40,40,12),(8,40,40,40,40,40,13),(8,40,40,40,40,40,14),(8,40,40,40,40,40,15),(8,40,40,40,40,40,16),(8,40,40,40,40,40,17),(8,40,40,40,40,40,18);
/*!40000 ALTER TABLE `monday_room_margin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `order_info`
--

DROP TABLE IF EXISTS `order_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `order_info` (
  `order_id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL,
  `order_date` int NOT NULL,
  `order_time` int NOT NULL,
  `order_room` int NOT NULL,
  `state_id` int NOT NULL,
  `startweek` int NOT NULL,
  `endweek` int NOT NULL,
  `order_amount` int NOT NULL,
  PRIMARY KEY (`order_id`),
  KEY `order_date` (`order_date`),
  KEY `order_time` (`order_time`),
  KEY `order_room` (`order_room`),
  KEY `state_id` (`state_id`),
  KEY `order_info_ibfk_1_idx` (`user_id`),
  CONSTRAINT `order_info_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`),
  CONSTRAINT `order_info_ibfk_2` FOREIGN KEY (`order_date`) REFERENCES `date_info` (`date_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `order_info_ibfk_3` FOREIGN KEY (`order_time`) REFERENCES `time_info` (`time_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `order_info_ibfk_4` FOREIGN KEY (`order_room`) REFERENCES `room_info` (`room_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `order_info_ibfk_5` FOREIGN KEY (`state_id`) REFERENCES `state_info` (`state_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `order_info`
--

LOCK TABLES `order_info` WRITE;
/*!40000 ALTER TABLE `order_info` DISABLE KEYS */;
/*!40000 ALTER TABLE `order_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `room_info`
--

DROP TABLE IF EXISTS `room_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `room_info` (
  `room_id` int NOT NULL AUTO_INCREMENT,
  `room_name` varchar(10) NOT NULL,
  `room_max_num` int NOT NULL,
  `room_type` int NOT NULL,
  PRIMARY KEY (`room_id`),
  UNIQUE KEY `room_name_UNIQUE` (`room_name`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `room_info`
--

LOCK TABLES `room_info` WRITE;
/*!40000 ALTER TABLE `room_info` DISABLE KEYS */;
INSERT INTO `room_info` VALUES (1,'1001',20,1),(2,'1003',30,1),(3,'1005',40,2),(8,'1011',40,3);
/*!40000 ALTER TABLE `room_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `saturday_room_margin`
--

DROP TABLE IF EXISTS `saturday_room_margin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `saturday_room_margin` (
  `room_id` int NOT NULL,
  `room_margin_1` int NOT NULL,
  `room_margin_2` int NOT NULL,
  `room_margin_3` int NOT NULL,
  `room_margin_4` int NOT NULL,
  `room_margin_5` int NOT NULL,
  `week` int NOT NULL,
  KEY `room_id` (`room_id`),
  CONSTRAINT `saturday_room_margin_ibfk_1` FOREIGN KEY (`room_id`) REFERENCES `room_info` (`room_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `saturday_room_margin`
--

LOCK TABLES `saturday_room_margin` WRITE;
/*!40000 ALTER TABLE `saturday_room_margin` DISABLE KEYS */;
INSERT INTO `saturday_room_margin` VALUES (1,20,20,20,20,20,1),(1,20,20,20,20,20,2),(1,20,20,20,20,20,3),(1,20,20,20,20,20,4),(1,20,20,20,20,20,5),(1,20,20,20,20,20,6),(1,20,20,20,20,20,7),(1,20,20,20,20,20,8),(1,20,20,20,20,20,9),(1,20,20,20,20,20,10),(1,20,20,20,20,20,11),(1,20,20,20,20,20,12),(1,20,20,20,20,20,13),(1,20,20,20,20,20,14),(1,20,20,20,20,20,15),(1,20,20,20,20,20,16),(1,20,20,20,20,20,17),(1,20,20,20,20,20,18),(2,30,30,30,30,30,1),(2,30,30,30,30,30,2),(2,30,30,30,30,30,3),(2,30,30,30,30,30,4),(2,30,30,30,30,30,5),(2,30,30,30,30,30,6),(2,30,30,30,30,30,7),(2,30,30,30,30,30,8),(2,30,30,30,30,30,9),(2,30,30,30,30,30,10),(2,30,30,30,30,30,11),(2,30,30,30,30,30,12),(2,30,30,30,30,30,13),(2,30,30,30,30,30,14),(2,30,30,30,30,30,15),(2,30,30,30,30,30,16),(2,30,30,30,30,30,17),(2,30,30,30,30,30,18),(3,40,40,40,40,40,1),(3,40,40,40,40,40,2),(3,40,40,40,40,40,3),(3,40,40,40,40,40,4),(3,40,40,40,40,40,5),(3,40,40,40,40,40,6),(3,40,40,40,40,40,7),(3,40,40,40,40,40,8),(3,40,40,40,40,40,9),(3,40,40,40,40,40,10),(3,40,40,40,40,40,11),(3,40,40,40,40,40,12),(3,40,40,40,40,40,13),(3,40,40,40,40,40,14),(3,40,40,40,40,40,15),(3,40,40,40,40,40,16),(3,40,40,40,40,40,17),(3,40,40,40,40,40,18),(8,40,40,40,40,40,1),(8,40,40,40,40,40,2),(8,40,40,40,40,40,3),(8,40,40,40,40,40,4),(8,40,40,40,40,40,5),(8,40,40,40,40,40,6),(8,40,40,40,40,40,7),(8,40,40,40,40,40,8),(8,40,40,40,40,40,9),(8,40,40,40,40,40,10),(8,40,40,40,40,40,11),(8,40,40,40,40,40,12),(8,40,40,40,40,40,13),(8,40,40,40,40,40,14),(8,40,40,40,40,40,15),(8,40,40,40,40,40,16),(8,40,40,40,40,40,17),(8,40,40,40,40,40,18);
/*!40000 ALTER TABLE `saturday_room_margin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `state_info`
--

DROP TABLE IF EXISTS `state_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `state_info` (
  `state_id` int NOT NULL AUTO_INCREMENT,
  `state_str` varchar(10) NOT NULL,
  PRIMARY KEY (`state_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `state_info`
--

LOCK TABLES `state_info` WRITE;
/*!40000 ALTER TABLE `state_info` DISABLE KEYS */;
INSERT INTO `state_info` VALUES (1,'待审核'),(2,'驳回'),(3,'通过');
/*!40000 ALTER TABLE `state_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sunday_room_margin`
--

DROP TABLE IF EXISTS `sunday_room_margin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `sunday_room_margin` (
  `room_id` int NOT NULL,
  `room_margin_1` int NOT NULL,
  `room_margin_2` int NOT NULL,
  `room_margin_3` int NOT NULL,
  `room_margin_4` int NOT NULL,
  `room_margin_5` int NOT NULL,
  `week` int NOT NULL,
  KEY `room_id` (`room_id`),
  CONSTRAINT `sunday_room_margin_ibfk_1` FOREIGN KEY (`room_id`) REFERENCES `room_info` (`room_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sunday_room_margin`
--

LOCK TABLES `sunday_room_margin` WRITE;
/*!40000 ALTER TABLE `sunday_room_margin` DISABLE KEYS */;
INSERT INTO `sunday_room_margin` VALUES (1,20,20,20,20,20,1),(1,20,20,20,20,20,2),(1,20,20,20,20,20,3),(1,20,20,20,20,20,4),(1,20,20,20,20,20,5),(1,20,20,20,20,20,6),(1,20,20,20,20,20,7),(1,20,20,20,20,20,8),(1,20,20,20,20,20,9),(1,20,20,20,20,20,10),(1,20,20,20,20,20,11),(1,20,20,20,20,20,12),(1,20,20,20,20,20,13),(1,20,20,20,20,20,14),(1,20,20,20,20,20,15),(1,20,20,20,20,20,16),(1,20,20,20,20,20,17),(1,20,20,20,20,20,18),(2,30,30,30,30,30,1),(2,30,30,30,30,30,2),(2,30,30,30,30,30,3),(2,30,30,30,30,30,4),(2,30,30,30,30,30,5),(2,30,30,30,30,30,6),(2,30,30,30,30,30,7),(2,30,30,30,30,30,8),(2,30,30,30,30,30,9),(2,30,30,30,30,30,10),(2,30,30,30,30,30,11),(2,30,30,30,30,30,12),(2,30,30,30,30,30,13),(2,30,30,30,30,30,14),(2,30,30,30,30,30,15),(2,30,30,30,30,30,16),(2,30,30,30,30,30,17),(2,30,30,30,30,30,18),(3,40,40,40,40,40,1),(3,40,40,40,40,40,2),(3,40,40,40,40,40,3),(3,40,40,40,40,40,4),(3,40,40,40,40,40,5),(3,40,40,40,40,40,6),(3,40,40,40,40,40,7),(3,40,40,40,40,40,8),(3,40,40,40,40,40,9),(3,40,40,40,40,40,10),(3,40,40,40,40,40,11),(3,40,40,40,40,40,12),(3,40,40,40,40,40,13),(3,40,40,40,40,40,14),(3,40,40,40,40,40,15),(3,40,40,40,40,40,16),(3,40,40,40,40,40,17),(3,40,40,40,40,40,18),(8,40,40,40,40,40,1),(8,40,40,40,40,40,2),(8,40,40,40,40,40,3),(8,40,40,40,40,40,4),(8,40,40,40,40,40,5),(8,40,40,40,40,40,6),(8,40,40,40,40,40,7),(8,40,40,40,40,40,8),(8,40,40,40,40,40,9),(8,40,40,40,40,40,10),(8,40,40,40,40,40,11),(8,40,40,40,40,40,12),(8,40,40,40,40,40,13),(8,40,40,40,40,40,14),(8,40,40,40,40,40,15),(8,40,40,40,40,40,16),(8,40,40,40,40,40,17),(8,40,40,40,40,40,18);
/*!40000 ALTER TABLE `sunday_room_margin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `thursday_room_margin`
--

DROP TABLE IF EXISTS `thursday_room_margin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `thursday_room_margin` (
  `room_id` int NOT NULL,
  `room_margin_1` int NOT NULL,
  `room_margin_2` int NOT NULL,
  `room_margin_3` int NOT NULL,
  `room_margin_4` int NOT NULL,
  `room_margin_5` int NOT NULL,
  `week` int NOT NULL,
  KEY `room_id` (`room_id`),
  CONSTRAINT `thursday_room_margin_ibfk_1` FOREIGN KEY (`room_id`) REFERENCES `room_info` (`room_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `thursday_room_margin`
--

LOCK TABLES `thursday_room_margin` WRITE;
/*!40000 ALTER TABLE `thursday_room_margin` DISABLE KEYS */;
INSERT INTO `thursday_room_margin` VALUES (1,20,20,20,20,20,1),(1,20,20,20,20,20,2),(1,20,20,20,20,20,3),(1,20,20,20,20,20,4),(1,20,20,20,20,20,5),(1,20,20,20,20,20,6),(1,20,20,20,20,20,7),(1,20,20,20,20,20,8),(1,20,20,20,20,20,9),(1,20,20,20,20,20,10),(1,20,20,20,20,20,11),(1,20,20,20,20,20,12),(1,20,20,20,20,20,13),(1,20,20,20,20,20,14),(1,20,20,20,20,20,15),(1,20,20,20,20,20,16),(1,20,20,20,20,20,17),(1,20,20,20,20,20,18),(2,30,30,30,30,30,1),(2,30,30,30,30,30,2),(2,30,30,30,30,30,3),(2,30,30,30,30,30,4),(2,30,30,30,30,30,5),(2,30,30,30,30,30,6),(2,30,30,30,30,30,7),(2,30,30,30,30,30,8),(2,30,30,30,30,30,9),(2,30,30,30,30,30,10),(2,30,30,30,30,30,11),(2,30,30,30,30,30,12),(2,30,30,30,30,30,13),(2,30,30,30,30,30,14),(2,30,30,30,30,30,15),(2,30,30,30,30,30,16),(2,30,30,30,30,30,17),(2,30,30,30,30,30,18),(3,40,40,40,40,40,1),(3,40,40,40,40,40,2),(3,40,40,40,40,40,3),(3,40,40,40,40,40,4),(3,40,40,40,40,40,5),(3,40,40,40,40,40,6),(3,40,40,40,40,40,7),(3,40,40,40,40,40,8),(3,40,40,40,40,40,9),(3,40,40,40,40,40,10),(3,40,40,40,40,40,11),(3,40,40,40,40,40,12),(3,40,40,40,40,40,13),(3,40,40,40,40,40,14),(3,40,40,40,40,40,15),(3,40,40,40,40,40,16),(3,40,40,40,40,40,17),(3,40,40,40,40,40,18),(8,40,40,40,40,40,1),(8,40,40,40,40,40,2),(8,40,40,40,40,40,3),(8,40,40,40,40,40,4),(8,40,40,40,40,40,5),(8,40,40,40,40,40,6),(8,40,40,40,40,40,7),(8,40,40,40,40,40,8),(8,40,40,40,40,40,9),(8,40,40,40,40,40,10),(8,40,40,40,40,40,11),(8,40,40,40,40,40,12),(8,40,40,40,40,40,13),(8,40,40,40,40,40,14),(8,40,40,40,40,40,15),(8,40,40,40,40,40,16),(8,40,40,40,40,40,17),(8,40,40,40,40,40,18);
/*!40000 ALTER TABLE `thursday_room_margin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `time_info`
--

DROP TABLE IF EXISTS `time_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `time_info` (
  `time_id` int NOT NULL AUTO_INCREMENT,
  `time_str` varchar(10) NOT NULL,
  PRIMARY KEY (`time_id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `time_info`
--

LOCK TABLES `time_info` WRITE;
/*!40000 ALTER TABLE `time_info` DISABLE KEYS */;
INSERT INTO `time_info` VALUES (1,'第一大节'),(2,'第二大节'),(3,'第三大节'),(4,'第四大节'),(5,'第五大节');
/*!40000 ALTER TABLE `time_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tuesday_room_margin`
--

DROP TABLE IF EXISTS `tuesday_room_margin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tuesday_room_margin` (
  `room_id` int NOT NULL,
  `room_margin_1` int NOT NULL,
  `room_margin_2` int NOT NULL,
  `room_margin_3` int NOT NULL,
  `room_margin_4` int NOT NULL,
  `room_margin_5` int NOT NULL,
  `week` int NOT NULL,
  KEY `room_id` (`room_id`),
  CONSTRAINT `tuesday_room_margin_ibfk_1` FOREIGN KEY (`room_id`) REFERENCES `room_info` (`room_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tuesday_room_margin`
--

LOCK TABLES `tuesday_room_margin` WRITE;
/*!40000 ALTER TABLE `tuesday_room_margin` DISABLE KEYS */;
INSERT INTO `tuesday_room_margin` VALUES (1,20,20,20,20,20,1),(1,20,20,20,20,20,2),(1,20,20,20,20,20,3),(1,20,20,20,20,20,4),(1,20,20,20,20,20,5),(1,20,20,20,20,20,6),(1,20,20,20,20,20,7),(1,20,20,20,20,20,8),(1,20,20,20,20,20,9),(1,20,20,20,20,20,10),(1,20,20,20,20,20,11),(1,20,20,20,20,20,12),(1,20,20,20,20,20,13),(1,20,20,20,20,20,14),(1,20,20,20,20,20,15),(1,20,20,20,20,20,16),(1,20,20,20,20,20,17),(1,20,20,20,20,20,18),(2,30,30,30,30,30,1),(2,30,30,30,30,30,2),(2,30,30,30,30,30,3),(2,30,30,30,30,30,4),(2,30,30,30,30,30,5),(2,30,30,30,30,30,6),(2,30,30,30,30,30,7),(2,30,30,30,30,30,8),(2,30,30,30,30,30,9),(2,30,30,30,30,30,10),(2,30,30,30,30,30,11),(2,30,30,30,30,30,12),(2,30,30,30,30,30,13),(2,30,30,30,30,30,14),(2,30,30,30,30,30,15),(2,30,30,30,30,30,16),(2,30,30,30,30,30,17),(2,30,30,30,30,30,18),(3,40,40,40,40,40,1),(3,40,40,40,40,40,2),(3,40,40,40,40,40,3),(3,40,40,40,40,40,4),(3,40,40,40,40,40,5),(3,40,40,40,40,40,6),(3,40,40,40,40,40,7),(3,40,40,40,40,40,8),(3,40,40,40,40,40,9),(3,40,40,40,40,40,10),(3,40,40,40,40,40,11),(3,40,40,40,40,40,12),(3,40,40,40,40,40,13),(3,40,40,40,40,40,14),(3,40,40,40,40,40,15),(3,40,40,40,40,40,16),(3,40,40,40,40,40,17),(3,40,40,40,40,40,18),(8,40,40,40,40,40,1),(8,40,40,40,40,40,2),(8,40,40,40,40,40,3),(8,40,40,40,40,40,4),(8,40,40,40,40,40,5),(8,40,40,40,40,40,6),(8,40,40,40,40,40,7),(8,40,40,40,40,40,8),(8,40,40,40,40,40,9),(8,40,40,40,40,40,10),(8,40,40,40,40,40,11),(8,40,40,40,40,40,12),(8,40,40,40,40,40,13),(8,40,40,40,40,40,14),(8,40,40,40,40,40,15),(8,40,40,40,40,40,16),(8,40,40,40,40,40,17),(8,40,40,40,40,40,18);
/*!40000 ALTER TABLE `tuesday_room_margin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `type_info`
--

DROP TABLE IF EXISTS `type_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `type_info` (
  `type_id` int NOT NULL,
  `type_str` varchar(45) NOT NULL,
  `user_id` int NOT NULL,
  PRIMARY KEY (`type_id`),
  UNIQUE KEY `type_str_UNIQUE` (`type_str`),
  KEY `user_id_idx` (`user_id`),
  CONSTRAINT `user_foreign` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `type_info`
--

LOCK TABLES `type_info` WRITE;
/*!40000 ALTER TABLE `type_info` DISABLE KEYS */;
INSERT INTO `type_info` VALUES (1,'硬件',2),(2,'软件',3),(3,'程序',5);
/*!40000 ALTER TABLE `type_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `user_id` int NOT NULL AUTO_INCREMENT,
  `user_name` varchar(45) NOT NULL,
  `user_password` varchar(45) NOT NULL,
  `user_permission` tinyint unsigned NOT NULL,
  `user_phone` varchar(45) DEFAULT NULL,
  `user_email` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`user_id`),
  UNIQUE KEY `user_name_UNIQUE` (`user_name`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'Admin','4a7d1ed414474e4033ac29ccb8653d9b',0,'15500000000','155@njust.edu.cn'),(2,'Teac1','81dc9bdb52d04dc20036dbd8313ed055',1,'13300000000','133@njust.edu.cn'),(3,'Teac2','81dc9bdb52d04dc20036dbd8313ed055',1,'17700000000','177@njust.edu.cn'),(4,'xiaoming','4a7d1ed414474e4033ac29ccb8653d9b',3,NULL,NULL),(5,'Teac3','81dc9bdb52d04dc20036dbd8313ed055',1,'18800000000','188@njust.edu.cn'),(6,'王雨翀','202cb962ac59075b964b07152d234b70',1,'133',''),(7,'A','81dc9bdb52d04dc20036dbd8313ed055',2,'123','111');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `wednesday_room_margin`
--

DROP TABLE IF EXISTS `wednesday_room_margin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `wednesday_room_margin` (
  `room_id` int NOT NULL,
  `room_margin_1` int NOT NULL,
  `room_margin_2` int NOT NULL,
  `room_margin_3` int NOT NULL,
  `room_margin_4` int NOT NULL,
  `room_margin_5` int NOT NULL,
  `week` int NOT NULL,
  KEY `room_id` (`room_id`),
  CONSTRAINT `wednesday_room_margin_ibfk_1` FOREIGN KEY (`room_id`) REFERENCES `room_info` (`room_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `wednesday_room_margin`
--

LOCK TABLES `wednesday_room_margin` WRITE;
/*!40000 ALTER TABLE `wednesday_room_margin` DISABLE KEYS */;
INSERT INTO `wednesday_room_margin` VALUES (1,20,20,20,20,20,1),(1,20,20,20,20,20,2),(1,20,20,20,20,20,3),(1,20,20,20,20,20,4),(1,20,20,20,20,20,5),(1,20,20,20,20,20,6),(1,20,20,20,20,20,7),(1,20,20,20,20,20,8),(1,20,20,20,20,20,9),(1,20,20,20,20,20,10),(1,20,20,20,20,20,11),(1,20,20,20,20,20,12),(1,20,20,20,20,20,13),(1,20,20,20,20,20,14),(1,20,20,20,20,20,15),(1,20,20,20,20,20,16),(1,20,20,20,20,20,17),(1,20,20,20,20,20,18),(2,30,30,30,30,30,1),(2,30,30,30,30,30,2),(2,30,30,30,30,30,3),(2,30,30,30,30,30,4),(2,30,30,30,30,30,5),(2,30,30,30,30,30,6),(2,30,30,30,30,30,7),(2,30,30,30,30,30,8),(2,30,30,30,30,30,9),(2,30,30,30,30,30,10),(2,30,30,30,30,30,11),(2,30,30,30,30,30,12),(2,30,30,30,30,30,13),(2,30,30,30,30,30,14),(2,30,30,30,30,30,15),(2,30,30,30,30,30,16),(2,30,30,30,30,30,17),(2,30,30,30,30,30,18),(3,40,40,40,40,40,1),(3,40,40,40,40,40,2),(3,40,40,40,40,40,3),(3,40,40,40,40,40,4),(3,40,40,40,40,40,5),(3,40,40,40,40,40,6),(3,40,40,40,40,40,7),(3,40,40,40,40,40,8),(3,40,40,40,40,40,9),(3,40,40,40,40,40,10),(3,40,40,40,40,40,11),(3,40,40,40,40,40,12),(3,40,40,40,40,40,13),(3,40,40,40,40,40,14),(3,40,40,40,40,40,15),(3,40,40,40,40,40,16),(3,40,40,40,40,40,17),(3,40,40,40,40,40,18),(8,40,40,40,40,40,1),(8,40,40,40,40,40,2),(8,40,40,40,40,40,3),(8,40,40,40,40,40,4),(8,40,40,40,40,40,5),(8,40,40,40,40,40,6),(8,40,40,40,40,40,7),(8,40,40,40,40,40,8),(8,40,40,40,40,40,9),(8,40,40,40,40,40,10),(8,40,40,40,40,40,11),(8,40,40,40,40,40,12),(8,40,40,40,40,40,13),(8,40,40,40,40,40,14),(8,40,40,40,40,40,15),(8,40,40,40,40,40,16),(8,40,40,40,40,40,17),(8,40,40,40,40,40,18);
/*!40000 ALTER TABLE `wednesday_room_margin` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-09-23 17:11:56
