% Variables
N = [110 80]; % "cm"
x = [0 1.1]; % m
y = [0 0.8]; % m
X = [x(1) linspace(x(1)+(x(2)/N(1))/2, x(2)-(x(2)/N(1))/2, N(1)) x(2)]; % m
Y = [y(1) linspace(y(1)+(y(2)/N(2))/2, y(2)-(y(2)/N(2))/2, N(2)) y(2)]; % m
t = 5000; % s

% Read file
input = uigetfile('*.txt');
data = dlmread(input, '\t');

% Fix matrix
T = data(2:end-1, 2:end-2); % remove extra elements
T = fixcorners(T); % average corners
T = flipud(rot90(T)); % orientation
T = T - 273.15; % Kelvin to Celsius

% Plot T map
figure;
hold('on');
imagesc(x, y, T);
contour(X, Y, T, 'ShowText', 'on', 'LineColor', 'black');
xlabel('$$x$$ (m)', 'Interpreter', 'latex');
ylabel('$$y$$ (m)', 'Interpreter', 'latex');
title(['Tempertautre Map at $t=' num2str(t) '\,$s'], 'Interpreter', 'latex');

function T = fixcorners(T)
    T(1,1) = mean([T(1, 2) T(2, 1)]);
    T(end,1) = mean([T(end-1, 1) T(end, 2)]);
    T(1,end) = mean([T(1, end-1) T(2, end)]);
    T(end,end) = mean([T(end, end-1) T(end-1,end)]);
end
