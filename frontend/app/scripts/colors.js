// Funktsioon, mis konverteerib HEX värvi RGBks
function hexToRgb(hex) {
    let bigint = parseInt(hex.slice(1), 16);
    let r = (bigint >> 16) & 255;
    let g = (bigint >> 8) & 255;
    let b = bigint & 255;
    return [r, g, b];
}

// Funktsioon RGB interpolatsiooni tegemiseks
function interpolateColor(color1, color2, factor) {
    let result = color1.slice();
    for (let i = 0; i < 3; i++) {
        result[i] = Math.round(result[i] + factor * (color2[i] - color1[i]));
    }
    return result;
}

// Funktsioon, mis konverteerib RGB värvi HEXiks
function rgbToHex(rgb) {
    return `#${rgb.map(x => x.toString(16).padStart(2, '0')).join('')}`;
}

// Funktsioon, mis genereerib värvide skaalad startColor ja endColor vahel
export function generateColors(startColor, endColor, steps) {
    const startRgb = hexToRgb(startColor);
    const endRgb = hexToRgb(endColor);
    let colors = [];

    for (let i = 0; i < steps; i++) {
        const factor = i / (steps - 1);
        const interpolatedColor = interpolateColor(startRgb, endRgb, factor);
        colors.push(rgbToHex(interpolatedColor));
    }

    return colors;
}