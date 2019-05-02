-- MySQL dump 10.16  Distrib 10.1.28-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: sneezy
-- ------------------------------------------------------
-- Server version	10.1.28-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `globaltoggles`
--

DROP TABLE IF EXISTS `globaltoggles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `globaltoggles` (
  `tog_id` int(11) NOT NULL,
  `toggle` tinyint(1) DEFAULT NULL,
  `testcode` tinyint(1) DEFAULT NULL,
  `name` varchar(80) DEFAULT NULL,
  `descr` varchar(256) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `globaltoggles`
--

LOCK TABLES `globaltoggles` WRITE;
/*!40000 ALTER TABLE `globaltoggles` DISABLE KEYS */;
INSERT INTO `globaltoggles` VALUES (1,0,0,'No-Shouting','allow shouting');
INSERT INTO `globaltoggles` VALUES (2,1,0,'Sleep offensive','sleep spell offensive');
INSERT INTO `globaltoggles` VALUES (4,1,0,'Gravity','gravity');
INSERT INTO `globaltoggles` VALUES (5,1,0,'Clients','allow connections with SneezyMUD client');
INSERT INTO `globaltoggles` VALUES (6,1,0,'Builder Wiznet','allow builders to hear wiznet');
INSERT INTO `globaltoggles` VALUES (7,1,0,'PCs w/mob names','allow PCs with mob names');
INSERT INTO `globaltoggles` VALUES (8,0,0,'Twinky Combat','twinky combat messages');
INSERT INTO `globaltoggles` VALUES (9,0,0,'Time DB Queries','time database queries');
INSERT INTO `globaltoggles` VALUES (10,0,0,'Game Loop Timing','print timing info for game loop');
INSERT INTO `globaltoggles` VALUES (11,0,0,'Double Exp','turn on double exp');
INSERT INTO `globaltoggles` VALUES (12,1,1,'Test Code 1','Queued player saves');
INSERT INTO `globaltoggles` VALUES (14,0,1,'Test Code 3','not currently used');
INSERT INTO `globaltoggles` VALUES (15,0,1,'Test Code 4','not currently used');
INSERT INTO `globaltoggles` VALUES (17,0,0,'DB Logging','log all db queries');
INSERT INTO `globaltoggles` VALUES (13,0,1,'Test Code 2','allow players to see item levels');
INSERT INTO `globaltoggles` VALUES (16,0,1,'Test Code 5','disable/enable certain aspects of the new faction code - dash');
INSERT INTO `globaltoggles` VALUES (18,0,1,'Quest Code 1','unknown');
INSERT INTO `globaltoggles` VALUES (19,0,1,'Quest Code 2','unknown');
INSERT INTO `globaltoggles` VALUES (20,0,1,'Quest Code 3','unknown');
INSERT INTO `globaltoggles` VALUES (21,0,1,'Quest Code 4','unknown');
INSERT INTO `globaltoggles` VALUES (3,0,0,'Newbie PK','allow PKing of newbies');
/*!40000 ALTER TABLE `globaltoggles` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-05-02 21:42:31
