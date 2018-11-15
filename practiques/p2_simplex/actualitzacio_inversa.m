function [invB] = actualitzacio_inversa(invB_antiga, db, p)
E = eye(size(db,1));
E(:,p) = -db./db(p);
E(p,p) = -1/db(p);
invB = E*invB_antiga;
endfunction
