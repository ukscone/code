(define make-tree list)
  
(define get-data car)
(define get-left cadr)
(define get-right caddr)

(define (is-leaf t) (and (null? (get-left t)) (null? (get-right t))))
  
(define (insert data tree comp)
   (cond ((null? tree) (make-tree data '() '()))
         ((comp data (get-data tree)) (make-tree (get-data tree) 
                                                 (insert data (get-left tree) comp) 
                                                 (get-right tree)))
         (else (make-tree (get-data tree) 
                          (get-left tree) 
                          (insert data (get-right tree) comp)))))
        
(define (lst->tree lst tree)
   (cond ((> (length lst) 1) (lst->tree (cdr lst) (insert (car lst) tree <=)))
         ((= (length lst) 1) (insert (car lst) tree <=))
         (else '())))
        
(define (in-order tree)
   (cond ((null? tree) '())
         (else (in-order (get-left tree)) (newline)
               (display (get-data tree)) (newline)
               (in-order (get-right tree)))))
             
(define (num-leaves tree)
   (cond ((null? tree) 0)
         ((is-leaf tree) 1)
         (else (+ (num-leaves (get-left tree)) (num-leaves (get-right tree))))))
         
(define (max-path tree)
  (if (null? tree)
      0
      (+ (max (max-path (get-left tree)) (max-path (get-right tree))) 1)))
       
(define (is-in data tree)
   (cond ((null? tree) #f)
         ((= data (get-data tree)) #t)
         ((< data (get-data tree)) (is-in data (get-left tree)))
         ((> data (get-data tree)) (is-in data (get-right tree)))))
       
       
(define tree1 (lst->tree (read) '()))
(in-order tree1)
(display (num-leaves tree1)) (newline)
(display (max-path tree1)) (newline)
(display (is-in (read) tree1)) (newline)
