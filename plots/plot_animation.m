% Variables
N = [110 80]; % "cm"
tOver = 10000+1; % s
step = 100; % s
x = [0 1.1]; % m
y = [0 0.8]; % m
X = [x(1) linspace(x(1)+(x(2)/N(1))/2, x(2)-(x(2)/N(1))/2, N(1)) x(2)]; % m
Y = [y(1) linspace(y(1)+(y(2)/N(2))/2, y(2)-(y(2)/N(2))/2, N(2)) y(2)]; % m

% Read file
input = 'input.txt'; % uigetfile('*.txt');
data = dlmread(input, '\t');

% Fix matrix
T = permute(reshape(data.', [N(2)+3 N(1)+2 tOver]), [2 1 3]); % time domain
T = T(2:end-1, 2:end-2, :); % remove extra elements
T = flipud(rot90(T)); % orientation
T = T - 273.15; % Kelvin to Celsius

% Plot T map
fig = figure;
loading = waitbar(0,'Generating...');
for k = 1:step:tOver
    hold('on');
    imagesc(x, y, T(:,:,k));
    contour(X, Y, T(:,:,k), 'ShowText', 'on', 'LineColor', 'black');
    xlabel('$$x$$ (m)', 'Interpreter', 'latex');
    ylabel('$$y$$ (m)', 'Interpreter', 'latex');
    title(['Tempertautre Map at $t=' num2str(k-1) '\,$s'], 'Interpreter', 'latex');
    
    f(k) = getframe(fig); %#ok<SAGROW>
    
    cla(fig); 
    waitbar(k/tOver);
end
close(loading);

% Render GIF
output = 'output.gif';
loading = waitbar(0,'Rendering...');
for k = 1:step:tOver
    im = frame2im(f(k));
    [in, cm] = rgb2ind(im, 256);
    
    if k  == 1
        imwrite(in, cm, output, 'gif', 'Loopcount', inf);
    else
        imwrite(in, cm, output, 'gif', 'WriteMode', 'append');
    end
    
    waitbar(k/tOver);
end
close(loading)

function T = fixcorners(T)
    T(1,1) = mean([T(1, 2) T(2, 1)]);
    T(end,1) = mean([T(end-1, 1) T(end, 2)]);
    T(1,end) = mean([T(1, end-1) T(2, end)]);
    T(end,end) = mean([T(end, end-1) T(end-1,end)]);
end
