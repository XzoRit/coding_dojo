(ns xzr
 (:use clojure.test))

(defn extract-separator [nums]
 (if (= \/ (first nums))
  [(subs nums 4) (re-pattern (str (.charAt nums 2)))]
  [nums (re-pattern ",|\n")]))

(defn split-by-separator [nums]
 (let [nums-and-sep (extract-separator nums)]
  (clojure.string/split (first nums-and-sep) (second nums-and-sep))))

(defn add [nums-as-str]
 (if (empty? nums-as-str)
  0
  (let [num-seq (->> (split-by-separator nums-as-str)
   (map #(Integer/parseInt %)))]
   (if (empty? (filter #(< % 0) num-seq))
    (reduce + 0 num-seq)
    (throw (IllegalArgumentException. "negative numbers not allowed"))))))

(deftest test-calling-add-with-empty-string-returns-0
 (is (= 0 (add ""))))

(deftest test-calling-add-with-one-number-returns-that-number
 (is (= 123 (add "123"))))

(deftest test-calling-with-two-nums-seperated-by-comma-returns-sum
 (is (= 23 (add "1,22"))))

(deftest test-calling-add-with-three-nums-seperated-by-comma-returns-sum
 (is (= 356 (add "1,22,333"))))

(deftest test-calling-add-with-negative-number-throws
 (is (thrown? IllegalArgumentException (add "1,-22,333"))))

(deftest test-calling-add-with-new-line-as-seperator-returns-sum
 (is (= 356 (add "1\n22,333"))))

(deftest test-support-for-delimiter-specifier
 (is (= 356 (add "//;\n1;22;333")))
 (is (= 356 (add "//-\n1-22-333"))))

(run-tests 'xzr)
