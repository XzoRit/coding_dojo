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
   (let [neg-pos (split-with neg? (sort num-seq))]
    (if (empty? (first neg-pos))
     (reduce + 0 (second neg-pos))
     (throw (IllegalArgumentException. (format "negative numbers %s not allowed" (vector (first neg-pos))))))))))

(deftest test-calling-add-with-empty-string-returns-0
 (is (= 0 (add ""))))

(deftest test-calling-add-with-one-number-returns-that-number
 (is (= 123 (add "123"))))

(deftest test-calling-with-two-nums-seperated-by-comma-returns-sum
 (is (= 23 (add "1,22"))))

(deftest test-calling-add-with-three-nums-seperated-by-comma-returns-sum
 (is (= 356 (add "1,22,333"))))

(deftest test-calling-add-with-new-line-as-seperator-returns-sum
 (is (= 356 (add "1\n22,333"))))

(deftest test-support-for-delimiter-specifier
 (is (= 356 (add "//;\n1;22;333")))
 (is (= 356 (add "//-\n1-22-333"))))

(deftest test-calling-add-with-negative-number-throws
 (is (thrown? IllegalArgumentException (add "1,-22,-333")))
 (try (add "1,-22,-333")
 (catch IllegalArgumentException e
  (is (= "java.lang.IllegalArgumentException: negative numbers [(-333 -22)] not allowed" (str e))))))

(run-tests 'xzr)
