(ns xzr.diamond
  (:require [clojure.string :as string])
  (:use clojure.test))

(defn letters [amount]
  (subs "ABCDEFGHIJKLMNOPQRSTUVWXYZ" 0 amount))

(defn spaces-after [amount]
  (map #(string/join (repeat % " ")) (range 0 amount)))

(defn spaces-before [amount]
  (reverse (spaces-after amount)))

(defn lines [amount]
  (map #(str %1 %2 %3) (spaces-before amount) (letters amount) (spaces-after amount)))

(defn drop-last [line]
  (subs line 0 (- (.length line) 1)))

(defn mirror-vertical [lines]
  (map str
   lines
   (->> lines
       (map drop-last)
       (map string/reverse))))

(deftest letters-returns-the-first-x-letters-of-the-alphabet
  (is (= "A" (letters 1)))
  (is (= "AB" (letters 2)))
  (is (= "ABC" (letters 3))))

(deftest spaces-after-returns-ascending-number-of-spaces
  (is (= '("") (spaces-after 1)))
  (is (= '("", " ") (spaces-after 2)))
  (is (= '("", " ", "  ") (spaces-after 3))))
  
(deftest spaces-before-returns-descending-number-of-spaces
  (is (= '("") (spaces-before 1)))
  (is (= '(" ", "") (spaces-before 2)))
  (is (= '("  ", " ", "") (spaces-before 3))))

(deftest lines-returns-upper-left-quadrant-of-diamond
  (is (= '("A") (lines 1)))
  (is (= '(" A", "B ") (lines 2)))
  (is (= '("  A", " B ", "C  ") (lines 3))))

(deftest lines-shall-be-mirrored-vertically
  (is (= '("A") (mirror-vertical '("A"))))
  (is (= '(" A ",
           "B B") (mirror-vertical '(" A", "B "))))
  (is (= '("  A  ",
           " B B ",
           "C   C") (mirror-vertical '("  A", " B ", "C  ")))))

(run-tests 'xzr.diamond)
