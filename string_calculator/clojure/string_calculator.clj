;; run script with clj <script-name>

(ns xzr
  (:use clojure.test))

(defn extract-separator-and-nums [nums-as-str]
  (if-let [[result] (re-seq #"//(.+)\n(.*)" nums-as-str)]
    (let  [[_ sep nums] result]
      [(re-pattern sep) nums])
    [#",|\n", nums-as-str]))

(defn split-by-separator [nums-as-string]
  (let [[sep nums] (extract-separator-and-nums nums-as-string)]
    (->>
     (clojure.string/split nums sep)
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

(deftest test-extract-separator-and-nums
  (let [[sep nums] (extract-separator-and-nums "//;\n1;22;333")]
    (is (= "1;22;333" nums))
    (is (= (str #";") (str sep))))
  (let [[sep nums] (extract-separator-and-nums "1,22,333")]
    (is (= "1,22,333" nums))
    (is (= (str #",|\n") (str sep))))
  (let [[sep nums] (extract-separator-and-nums "//-T-\n1-T-22-T-333")]
    (is (= "1-T-22-T-333" nums))
    (is (= (str #"-T-") (str sep)))))

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

(run-tests 'xzr)
