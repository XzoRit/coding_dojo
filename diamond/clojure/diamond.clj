(ns xzr.diamond
  (:require [clojure.string :as string])
  (:use clojure.test))

(defn letters [amount]
  (subs "ABCDEFGHIJKLMNOPQRSTUVWXYZ" 0 amount))

(defn spaces-after [amount]
  (map #(string/join (repeat % " ")) (range 0 amount)))

(defn spaces-before [amount]
  (reverse (spaces-after amount)))

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
  
(run-tests 'xzr.diamond)
