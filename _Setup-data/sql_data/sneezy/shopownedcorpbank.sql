-- MariaDB dump 10.18  Distrib 10.5.8-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: sneezy-db    Database: sneezy
-- ------------------------------------------------------
-- Server version	10.5.8-MariaDB-1:10.5.8+maria~focal

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `shopownedcorpbank`
--

DROP TABLE IF EXISTS `shopownedcorpbank`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `shopownedcorpbank` (
  `shop_nr` int(11) DEFAULT NULL,
  `corp_id` int(11) DEFAULT NULL,
  `talens` int(11) DEFAULT NULL,
  `earned_interest` double DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `shopownedcorpbank`
--

LOCK TABLES `shopownedcorpbank` WRITE;
/*!40000 ALTER TABLE `shopownedcorpbank` DISABLE KEYS */;
INSERT INTO `shopownedcorpbank` VALUES (4,12,2165070,0.407123286337651),
(4,4,0,0.179890271132535),
(4,8,2264175,0.418904108871686),
(4,17,4486377,0.201479441898073),
(4,2,2000000,0.139658630136985),
(4,16,2000000,0),
(4,6,2000000,0.145150654634108),
(4,11,2000000,0.781041095812901),
(4,3,2000000,0.794410882561351),
(4,13,2121990,0.074246575310597),
(4,10,0,0.17528766347823),
(142,27,0,0.904644869869704),
(142,25,2000000,0.338996710745818),
(141,28,2048471,0.164383560673741),
(141,24,2000572,0.331506849160178),
(140,29,0,0.52465753357319),
(140,23,2000000,0),
(4,21,4954061,0.89145198517781),
(142,7,2000000,0.876767115080947);
/*!40000 ALTER TABLE `shopownedcorpbank` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-05-03 20:19:04
