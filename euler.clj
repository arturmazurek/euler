(defn divisible-by-3-5? [num] (or (= 0 (mod num 3)) (= 0 (mod num 5))))
(defn problem1[] (reduce #(+ %1 %2) (filter divisible-by-3-5? (range 1 1000))))

(defn next-fibonacci[[a, b]] [b, (+ a b)])

(println (problem1))