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

(defn string-drop-last [line]
  (subs line 0 (- (.length line) 1)))

(defn mirror-vertical [lines]
  (map str
   lines
   (->> lines
       (map string-drop-last)
       (map string/reverse))))

(defn mirror-horizontal [lines]
  (reduce #(concat %1 (list %2)) lines (reverse (drop-last lines))))

(defn create [char-for-longest-line]
  (let [amount (inc (- (int char-for-longest-line) (int \A)))]
    (reduce #(str %1 %2 "\n") "" (mirror-horizontal (mirror-vertical (lines amount))))))

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

(deftest lines-shall-be-mirrored-horizontally
  (is (= '("A") (mirror-horizontal '("A"))))
  (is (= '(" A",
           "B ",
           " A") (mirror-horizontal '(" A", "B "))))
  (is (= '("  A",
           " B ",
           "C  ",
           " B ",
           "  A") (mirror-horizontal '("  A", " B ", "C  ")))))

(deftest create-shall-return-string-with-given-character-as-the-longest-line
  (is (= "A\n" (create \A)))
  (is (= (str " A \n"
              "B B\n"
              " A \n") (create \B)))
  (is (= (str "  A  \n"
              " B B \n"
              "C   C\n"
              " B B \n"
              "  A  \n") (create \C))))

(run-tests 'xzr.diamond)

(print (map create (seq "ABCDEFGHIJKLMNOPQRSTUVWXYZ")))
