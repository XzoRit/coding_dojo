(ns xzr
  (:use clojure.test))

(defn pop-front-digit
  [num]
  (map #(mod num %) [10000 1000 100 10]))

(defn extract-front-digit
  [nums]
  (map #(int (/ %1 %2)) nums [1000 100 10 1]))

(defn digits-of
  [num]
  (->
   (pop-front-digit num)
   (extract-front-digit)))
            
(def ones ["" "I" "II" "III" "IV" "V" "VI" "VII" "VIII" "IX"])
(def tens ["" "X" "XX" "XXX" "XL" "L" "LX" "LXX" "LXXX" "XC"])
(def hundreds ["" "C" "CC" "CCC" "CD" "D" "DC" "DCC" "DCCC" "CM"])
(def thousands ["" "M" "MM" "MMM"])
(def symbol-table [thousands hundreds tens ones])

(defn map-to-symbol
  [digits]
  (map #(%1 %2) symbol-table digits))

(defn concat-symbols
  [symbols]
  (reduce #(str %1 %2) "" symbols))

(defn arabic-to-roman
  [arabic]
  (->
   (digits-of arabic)
   (map-to-symbol)
   (concat-symbols)))

(deftest test-pop-front-digit
  (is (= (pop-front-digit 1234) [1234 234 34 4]))
  (is (= (pop-front-digit 4321) [4321 321 21 1])))
  
(deftest test-extract-front-digit
  (is (= (extract-front-digit [1234 234 34 4]) [1 2 3 4]))
  (is (= (extract-front-digit [4321 321 21 1]) [4 3 2 1])))
  
(deftest test-digits-of
  (is (= (digits-of 0) [0 0 0 0]))
  (is (= (digits-of 1234) [1 2 3 4]))
  (is (= (digits-of 4321) [4 3 2 1])))

(deftest test-map-to-symbol
  (is (= (map-to-symbol [0 0 0 0]) ["" "" "" ""]))
  (is (= (map-to-symbol [1 1 1 1]) ["M" "C" "X" "I"]))
  (is (= (map-to-symbol [3 3 3 3]) ["MMM" "CCC" "XXX" "III"]))
  (is (= (map-to-symbol [0 4 4 4]) ["" "CD" "XL" "IV"]))
  (is (= (map-to-symbol [0 9 9 9]) ["" "CM" "XC" "IX"])))

(deftest test-concat-symbols
  (is (= (concat-symbols ["" "" "" ""]) ""))
  (is (= (concat-symbols ["M" "C" "X" "I"]) "MCXI"))
  (is (= (concat-symbols ["MMM" "CCC" "XXX" "III"]) "MMMCCCXXXIII"))
  (is (= (concat-symbols ["" "CD" "XL" "IV"]) "CDXLIV"))
  (is (= (concat-symbols ["" "CM" "XC" "IX"]) "CMXCIX")))

(deftest test-arabic-to-roman
  (is (= (arabic-to-roman 1981) "MCMLXXXI")))

(run-tests 'xzr)
