;; run script with clj <script-name>

(ns xzr
  (:use clojure.test))

(defn extract-nums-and-separator [nums-as-str]
  (if-let [[result] (re-seq #"//(.)\n(.*)" nums-as-str)]
    (let  [[_ sep nums] result]
      [sep nums])
    [",|\\n", nums-as-str]))

(defn extract-separator [nums]
  (if (= \/ (first nums))
    [(subs nums 4) (re-pattern (str (.charAt nums 2)))]
    [nums (re-pattern ",|\\n")]))

(defn split-by-separator [nums-as-string]
  (let [[sep nums] (extract-nums-and-separator nums-as-string)]
    (->>
     (clojure.string/split nums (re-pattern sep))
     (map #(Integer/parseInt %)))))

(defn add [nums-as-str]
  (if (empty? nums-as-str)
    0
    (let [[negatives positives]
          (->>
           (split-by-separator nums-as-str)
           (sort)
           (split-with neg?))]
      (if (empty? negatives)
        (reduce + 0 positives)
        (throw (IllegalArgumentException. (format "negative numbers %s not allowed" [negatives])))))))

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
  (is (= 356 (add "//;\n1;22;333"))))

(deftest test-calling-add-with-negative-number-throws
  (is (thrown? IllegalArgumentException (add "1,-22,-333")))
  (try (add "1,-22,-333")
       (catch IllegalArgumentException e
         (is (= "java.lang.IllegalArgumentException: negative numbers [(-333 -22)] not allowed" (str e))))))

(deftest test-extract-separator
  (let [[nums sep] (extract-separator "1,22,333")]
    (is (= "1,22,333" nums))
    (is (= (str #",|\n") (str sep))))
  (let [[nums sep] (extract-separator "//;\n1;22;333")]
    (is (= "1;22;333" nums))
    (is (= (str #";") (str sep)))))

(deftest test-extract-nums-and-separator
  (is (= [";" "1;22;333"] (extract-nums-and-separator "//;\n1;22;333")))
  (is (= [",|\\n" "1,22,333"] (extract-nums-and-separator "1,22,333"))))

(run-tests 'xzr)
