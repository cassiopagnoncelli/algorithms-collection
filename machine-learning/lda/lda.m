clear all
x1 = load('data1.txt');
x2 = load('data2.txt');
%p = load('prior.txt') ;

for i = 1:60
    x1(i,1) = normrnd(2,1);
    x1(i,2) = normrnd(2,1);
end
for i = 1:60
    x2(i,1) = normrnd(5,1);
    x2(i,2) = normrnd(5,1);
end

p = [.5, .5] ;

plot(x1(:,1), x1(:,2), 'bx');
hold
plot(x2(:,1), x2(:,2), 'rx')

[lin1, co11] =size(x1);
[lin2, col2] =size(x2);

mu_1 = mean(x1);
plot(mu_1(:,1), mu_1(:,2), 'bd');
mu_2 = mean(x2);
plot(mu_2(:,1), mu_2(:,2), 'rd');

mu= (mu_1 + mu_2)/2 ;
plot(mu(:,1), mu(:,2), 'kd');

for i = 1:lin1
    x1_temp(i,:) = x1(i,:) - mu;
end

for i = 1:lin2
    x2_temp(i,:) = x2(i,:) - mu;
end

c1 = cov(x1_temp);
c2 = cov(x2_temp);

[lin,col] = size(c1);
for i = 1:lin
    for j = 1:col
        C(i,j)= p(1) * c1(i,j) + p(2) * c2(i,j);
    end
end

Cinv = inv(C);


figure ;
hold on ;
rec = 0 ;

for i = 1:lin1
    f1 = mu_1*Cinv*x1(i,:)'-0.5*mu_1*Cinv*mu_1';
    f2 = mu_2*Cinv*x1(i,:)'-0.5*mu_2*Cinv*mu_2';
    if(f1 > f2)
        plot(f1,f2, 'b*') ;
        rec = rec +1 ;
    else
        plot(f1,f2, 'r*') ;   
    end
end

for i = 1:lin2
    f1 = mu_1*Cinv*x2(i,:)'-0.5*mu_1*Cinv*mu_1';
    f2 = mu_2*Cinv*x2(i,:)'-0.5*mu_2*Cinv*mu_2';
    if(f1 > f2)
        plot(f1,f2, 'b*') ;
    else
        plot(f1,f2, 'r*') ;   
        rec = rec+1 ;
    end
end

rec/(lin1 + lin2) 
