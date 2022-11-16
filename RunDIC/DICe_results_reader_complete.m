% Read DICe exit files and save to mat format
function [v,u,X,Y] = DICe_results_reader_complete(nc,step_dic)

% LEGEND FOR OUTPUT PARAMETERS (see DICe documentation)
% 1 - # of subset
% 2 - X (subs coord, x)
% 3 - Y (subs coord, y)
% 4 - ux (subs horiz displ)
% 5 - uy (subs vert displ)
% 6 - sigma
% 7 - gamma
% 8 - beta
% 9 - status_flag
% 10 - uncertainty
% 11 - exx
% 12 - eyy
% 13 - exy

A = csvread('solution\DICe_solution_0.txt',2);
% 1-# 2-X 3-Y 4-u 5-exx ecc.

% Modify columns of B to include the parameters of interest
% Default: % 1-#subsets 2-X 3-Y 4-ux 5-uy
B = [A(:,1:4) A(:,5)];
B = sortrows(B,[2 3]);
minx = min(B(:,2));
maxx = max(B(:,2));
miny = min(B(:,3));
maxy = max(B(:,3));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Eventually modify this part depending on the variables of interest
v = zeros( (maxy-miny)/step_dic , (maxx-minx)/step_dic);
u = v;
X = v;
Y = v;

for ii = 1 : length(B)
    v((B(ii,3)-miny)/step_dic+1,(B(ii,2)-minx)/step_dic+1) = B(ii,5);
    u((B(ii,3)-miny)/step_dic+1,(B(ii,2)-minx)/step_dic+1) = B(ii,4);
    X((B(ii,3)-miny)/step_dic+1,(B(ii,2)-minx)/step_dic+1) = B(ii,2);
    Y((B(ii,3)-miny)/step_dic+1,(B(ii,2)-minx)/step_dic+1) = B(ii,3);
end

% save mat file
save(['.\mat files\output_',num2str(nc),'.mat'],'u','v','X','Y')
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

end
