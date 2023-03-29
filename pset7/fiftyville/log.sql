-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE year = 2021 AND  month = 7 AND day = 28;
-- 10:15am, 3 witnesses, Humphrey St bakery.
SELECT transcript FROM interviews WHERE day = 28 AND month = 7 AND year = 2021;
-- within 10m of theft. thief gets into car in bakery parking lot. Someone recogniseable. Thief withdrawing money by ATM on Leggett Street earlier in the morning.
-- Thief called someone while leaving the bakery, earliest flight out of fiftyville. Asked the receiver to purchase the ticket. Robert & Patrick, Paris?
SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10;
-- 13FNH73 Sophia, 94KL13X Bruce, G412CB7 Sofia, 322W7JE Diana, 0NTHK55 Kelsey

SELECT * FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street";
SELECT * FROM atm_transactions JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street";
SELECT * FROM bakery_security_logs JOIN people ON people.license_plate = bakery_security_logs.license_plate WHERE day = 28 AND month = 7 AND hour = 10;
SELECT * FROM phone_calls JOIN people ON people.phone_number = phone_calls.caller WHERE day = 28 AND month = 7 AND duration < 60;
SELECT * FROM atm_transactions JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number JOIN people ON people.id = bank_accounts.person_id WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street";