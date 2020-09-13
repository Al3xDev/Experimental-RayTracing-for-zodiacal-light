#version 450 core
in vec3 pos;
out vec4 FragColor;

uniform highp vec3 sun_pos;
uniform highp float steps;
uniform highp float Dmax;
uniform highp float sun_intens;


highp float dens_gauss( highp float d)
{
    highp float e = 2.718281828;
    highp float alpha = 1.0;
    highp float beta =  -1.0e16; //neg.!!!
    highp float w = d/beta*d;

    return alpha * pow( e, w);
}

void main()
{
    highp float step_size = Dmax / float( steps);
    highp float D = 1.496e8;
    highp float Rp = 6371.0;


	highp vec3 dir = normalize( vec3( pos.x, pos.y, 1));

    if( length( vec2(pos.x + Rp, pos.y)) < Rp)
    {
        FragColor = vec4( 0, 0.45, 0.30, 1);
    }
    else
    {
        highp vec3 v;
        highp float it = 0;
        highp float r1 = 0, r2 = 0;


        for( float i=1; i< steps; ++i)
        {
            v =  sun_pos - i * step_size * dir;
            r1 = length( v);
            r2 = i*step_size;

            it = it + ( sun_intens/(r1*r1)/(r2*r2)*dens_gauss( r1)* dot( dir, normalize(v)));
        }

        FragColor = vec4( it, it, it, 1);
    }
}
