#!/bin/bash

output_file=$1

# Initialisation du fichier
cat > "$output_file" <<EOF
camera:
{
    resolution = {
        width = 1920;
        height = 1080; # 1200 * 9 / 16 = 675
    };
    position = {
        x = 13.0;
        y = 2.0;
        z = 3.0;
    };
    rotation = {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    };
    fieldOfView = 20.0;
    defocusAngle = 0.6;
    focusDistance = 10.0;
    maxDepth = 10;
    samplesPerPixel = 10;
    pixelSampleScale = 0.1; # 1.0 / samples_per_pixel
};

primitives:
{
    spheres = (

        # Sol
        {
            position = {
                x = 0.0;
                y = -1000.0;
                z = 0.0;
            };
            r = 1000.0;
            color = {
                r = "50%";
                g = "50%";
                b = "50%";
            };
        },

        # Grande sphère en verre
        {
            position = {
                x = 0.0;
                y = 1.0;
                z = 0.0;
            };
            r = 1.0;
            refraction = "75%";
        },

        # Grande sphère diffuse
        {
            position = {
                x = -4.0;
                y = 1.0;
                z = 0.0;
            };
            r = 1.0;
            color = {
                r = "40%";
                g = "20%";
                b = "10%";
            };
        },

        # Grande sphère métallique
        {
            position = {
                x = 4.0;
                y = 1.0;
                z = 0.0;
            };
            r = 1.0;
            color = {
                r = "70%";
                g = "60%";
                b = "50%";
            };
            reflection = "100%";
        },
EOF

SEED=$(date +%s)

for a in $(seq -11 10); do
    for b in $(seq -11 10); do
        cx=$(awk -v a=$a -v s=$SEED 'BEGIN { srand(s + a*1000 + b); printf "%.3f", a + 0.9 * rand() }')
        cz=$(awk -v b=$b -v s=$SEED 'BEGIN { srand(s + a*1000 + b + 1); printf "%.3f", b + 0.9 * rand() }')
        cy=0.2

        dist=$(awk -v x=$cx -v z=$cz 'BEGIN { d = (x - 4)^2 + (z)^2; print (sqrt(d) <= 0.9) ? 1 : 0 }')
        [ "$dist" -eq 1 ] && continue

        mat=$(awk -v s=$SEED -v a=$a -v b=$b 'BEGIN { srand(s + a*1000 + b + 2); print rand() }')

        if awk "BEGIN { exit !($mat < 0.8) }"; then
            # Diffuse
<<<<<<<< HEAD:random_spheres.sh
            r=$(awk -v s=$SEED -v a=$a -v b=$b 'BEGIN { srand(s + a*1000 + b + 3); print rand() * rand() }')
            g=$(awk -v s=$SEED -v a=$a -v b=$b 'BEGIN { srand(s + a*1000 + b + 4); print rand() * rand() }')
            bval=$(awk -v s=$SEED -v a=$a -v b=$b 'BEGIN { srand(s + a*1000 + b + 5); print rand() * rand() }')
            ty=$(awk -v s=$SEED -v a=$a -v b=$b 'BEGIN { srand(s + a*1000 + b + 99); printf "%.3f", rand() * 0.5 }')
========
            rval=$(awk -v s=$SEED -v a=$a -v b=$b 'BEGIN { srand(s + a*1000 + b + 3); print rand() * rand() * 100 }')
            gval=$(awk -v s=$SEED -v a=$a -v b=$b 'BEGIN { srand(s + a*1000 + b + 4); print rand() * rand() * 100 }')
            bval=$(awk -v s=$SEED -v a=$a -v b=$b 'BEGIN { srand(s + a*1000 + b + 5); print rand() * rand() * 100 }')
>>>>>>>> origin/main:scenes/generate_spheres_scenes.sh

            cat >> "$output_file" <<EOF
        {
            position = { x = $cx; y = $cy; z = $cz; };
            r = 0.2;
            color = {
                r = "$rval%";
                g = "$gval%";
                b = "$bval%";
            };
            translation = {
                x = 0.0;
                y = $ty;
                z = 0.0;
            };
        },
EOF

        elif awk "BEGIN { exit !($mat < 0.95) }"; then
            # Metal
            rval=$(awk -v s=$SEED -v a=$a -v b=$b 'BEGIN { srand(s + a*1000 + b + 6); print 0.5 + rand() * 0.5 * 100 }')
            gval=$(awk -v s=$SEED -v a=$a -v b=$b 'BEGIN { srand(s + a*1000 + b + 7); print 0.5 + rand() * 0.5 * 100 }')
            bval=$(awk -v s=$SEED -v a=$a -v b=$b 'BEGIN { srand(s + a*1000 + b + 8); print 0.5 + rand() * 0.5 * 100 }')
            fuzz=$(awk -v s=$SEED -v a=$a -v b=$b 'BEGIN { srand(s + a*1000 + b + 9); print rand() * 0.5 * 100 }')

            cat >> "$output_file" <<EOF
        {
            position = { x = $cx; y = $cy; z = $cz; };
            r = 0.2;
            color = {
                r = "$rval%";
                g = "$gval%";
                b = "$bval%";
            };
            reflection = "$fuzz%";
        },
EOF

        else
            # Dielectric
            cat >> "$output_file" <<EOF
        {
            position = { x = $cx; y = $cy; z = $cz; };
            r = 0.2;
            refraction = "75%";
        },
EOF
        fi
    done
done

# Fermeture du bloc
echo "    );" >> "$output_file"
echo "};" >> "$output_file"

echo "✅ Fichier généré avec translations : $output_file"
