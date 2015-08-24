function [A,e] = recurse(B,x,y,f)

    [r,c,d] = size(B);
    B(y,x) = 0;
    
    if(f<800)
        e=0;
        if(y+1<=r)
            if(B(y+1,x)==1)
                f=f+1;
                [B,e] = recurse(B,x,y+1,f);
            end
        end
        if((y+1<=r)&&(x+1<=c)&&f<800)
            if(B(y+1,x+1)==1)
                f=f+1;
                [B,e] = recurse(B,x+1,y+1,f);
            end
        end
        if((y+1<=r)&&(x-1>0)&&f<800)
            if(B(y+1,x-1)==1)
                f=f+1;
                [B,e] = recurse(B,x-1,y+1,f);
            end
        end
        if(y-1>0&&f<800)
            if(B(y-1,x)==1)
                f=f+1;
                [B,e] = recurse(B,x,y-1,f);
            end
        end
        if((y-1>0)&&(x+1<=c)&&f<800)
            if(B(y-1,x+1)==1)
                f=f+1;
                [B,e] = recurse(B,x+1,y-1,f);
            end
        end
        if((y-1>0)&&(x-1>0)&&f<800)
            if(B(y-1,x-1)==1)
                f=f+1;
                [B,e] = recurse(B,x-1,y-1,f);
            end
        end
        if(x-1>0&&f<800)
            if(B(y,x-1)==1)
                f=f+1;
                [B,e] = recurse(B,x-1,y,f);
            end
        end
        if(x+1<=c&&f<800)
            if(B(y,x+1)==1)
                f=f+1;
                [B,e] = recurse(B,x+1,y,f);
            end
        end
    end
    if(f>799)
        e=1;
    end
    
    A=B;
end

