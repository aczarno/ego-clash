#############################################################
# Convert from OSM -> CDF
#
$script_rev = "1.12";
$script_date = "01/15/08";
#
#############################################################

$lines = 0;
$no_warn = 1;
$no_rep_warn = 1;
$objects_started = 0;

if(@ARGV < 1) 
{
    print "#####################################################################\n";
    print "#\n";
    print "#    OSM2CDF Converter: Version $script_rev   Date $script_date\n";
    print "#\n";
    print "#    Usage:\n";
    print "#    perl OSM2CDF.pl \"input.osm\"  > \"output.cdf\"\n";
    print "#\n";
    print "#\n";
    print "#####################################################################\n";
    print "\n";

    die;
}

$fname = $ARGV[0];
open(FNAME, "<$fname") || die "Can't open $fname: $!\n";

while($file[$lines] = <FNAME>)
{
    $lines++;
}

print "<!-- Created with rev $script_rev of osm2cdf.pl - release date:$script_date -->\n";

for($i=0; $i<$lines; $i++)
{
    $line = $file[$i];
    chomp($line);
    
    if($line =~ /<oe_scene>/i)
    {
        $ARGV[0] =~ s/\.osm//i;
        print "<Scene Name=\"$ARGV[0]\">\n\n";
        print "    <Properties SystemType=\"Geometry\">\n";
        print "    <\/Properties>\n\n";
    }
    elsif($line =~ /<\/oe_scene>/i)
    {
        print "<\/Scene>\n";
    }
    elsif($line =~ /<scenemanager/i)
    {
    }
    elsif($line =~ /<bkgcolor/i)
    {
    }
    elsif($line =~ /<lightcolor\s*r=\"(-?[0-9\.]*)\"\s*g=\"(-?[0-9\.]*)\"\s*b=\"(-?[0-9\.]*)\"/i)
    {
        print "    <Properties SystemType=\"Graphics\">\n";
        print "        <Property Name=\"AmbientLight\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\"\/>\n";
    }
    elsif($line =~ /<shadowtechnique type=\"(-?[0-9]*)\" tex_size=\"(-?[0-9]*)\" tex_count=\"(-?[0-9]*)\">/i)
    {
	print "        <!--\n";
	print "           Shadow Value1\'s:\n";
	print "           SHADOWTYPE_NONE             = 0\n";
	print "           SHADOWTYPE_TEXTURE_ADDITIVE = 33\n";
	print "          -->\n";
        print "        <!--Property Name=\"Shadows\" Value1=\"$1\" Value2=\"0\"-->\n";
        print "        <Property Name=\"Shadows\" Value1=\"33\" Value2=\"0\"\/>\n";
        if($file[$i+1] =~ /<color\s*r=\"(-?[0-9\.]*)\"\s*g=\"(-?[0-9\.]*)\"\s*b=\"(-?[0-9\.]*)\"/i)
        {
            print "        <Property Name=\"ShadowColor\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\"\/>\n";
            $i++;
        }
    }
    elsif($line =~ /<\/shadowtechnique/i)
    {
        print "    <\/Properties>\n\n";

        print "    <Properties SystemType=\"Audio\">\n";
        print "    <\/Properties>\n";
        print "    <Properties SystemType=\"Input\">\n";
        print "    <\/Properties>\n";
        print "    <Properties SystemType=\"PhysicsCollision\">\n";
        print "        <Property Name=\"Gravity\" Value1=\"0.0\" Value2=\"-500.0\" Value3=\"0.0\"\/>\n";
        print "    <\/Properties>\n";
        print "    <Properties SystemType=\"ProceduralTrees\">\n";
        print "    <\/Properties>\n";
        print "    <Properties SystemType=\"ProceduralFire\">\n";
        print "    <\/Properties>\n";
        print "    <Properties SystemType=\"VolumetricFlames\">\n";
        print "    <\/Properties>\n";
    }
    elsif(($line =~ /<lights/i) || ($line =~ /<entities/i))# || ($line =~ /<cameras/i))
    {
        if($objects_started++ == 0)
        {
            print "    <Objects>\n";
        }
    }
    elsif($line =~ /<light\s*name=\"(.*)\"\s*type=\"(.*)\"\s*on=\"(.*)\"\s*CastShadows=\"(.*)\"\s*intensity=\"(.*)\"/i)
    {

        print "        <Object Name=\"$1\">\n";
        print "            <Properties SystemType=\"Graphics\" ObjectType=\"Light\">\n";
        print "                <Property Name=\"Type\" Value1=\"";
        if($2 =~ /omni/i)
        {
            print "Point";
        }
        elsif($2 =~ /spot/i)
        {
            print "Spot";
        }
	else
        {
            print "!!!! ERROR: I DON'T UNDERSTAND THIS TYPE YET !!!!";
        }
        print "\"\/>\n";
        while(!($file[++$i] =~ /<\/light/i))
        {
            $line = $file[$i];
            chomp($line);

            if($line =~ /position\s*x=\"(-?[0-9\.]*)\"\s*y=\"(-?[0-9\.]*)\"\s*z=\"(-?[0-9\.]*)\"/i)
            {
                print "                <Property Name=\"Position\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\"\/>\n";
            }
            elsif($line =~ /color\s*r=\"(-?[0-9\.]*)\"\s*g=\"(-?[0-9\.]*)\"\s*b=\"(-?[0-9\.]*)\"/i)
            {
                print "                <Property Name=\"Diffuse\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\"\/>\n";
            }
            elsif($line =~ /specular\s*r=\"(-?[0-9\.]*)\"\s*g=\"(-?[0-9\.]*)\"\s*b=\"(-?[0-9\.]*)\"/i)
            {
                print "                <Property Name=\"Specular\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\"\/>\n";
            }
            elsif($line =~ /rotation\s*x=\"(-?[0-9\.]*)\"\s*y=\"(-?[0-9\.]*)\"\s*z=\"(-?[0-9\.]*)\"\s*w=\"(-?[0-9\.]*)\"/i)
            {
                print "                <!--<Property Name=\"Orientation\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\" Value4=\"$4\"\/>-->\n";
            }
            elsif($line =~ /scale\s*x=\"(-?[0-9\.]*)\"\s*y=\"(-?[0-9\.]*)\"\s*z=\"(-?[0-9\.]*)\"/i)
            {
                print "                <!--<Property Name=\"Scale\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\"\/>-->\n";
            }
            else
            {
                print "                <!-- $line -->\n";
            }
        }
        $i--;
        print "            <\/Properties>\n";
        print "        <\/Object>\n";
    }
    elsif($line =~ /<\/light/i)
    {
    }
    elsif($line =~ /<\/lights/i)
    {
    }
#    elsif($line =~ /<camera\s*name=\"(.*)\"\s*type=\"(.*)\"/i)
#    {
#        print "        <!--<Object Name=\"$1\">-->\n";
#        print "            <!--<Properties SystemType=\"Graphics\" ObjectType=\"Camera\">-->\n";
#        while(!($file[++$i] =~ /<\/camera/i))
#        {
#            $line = $file[$i];
#            chomp($line);
    #
    #        if($line =~ /position\s*x=\"(-?[0-9\.]*)\"\s*y=\"(-?[0-9\.]*)\"\s*z=\"(-?[0-9\.]*)\"/i)
    #        {
    #            print "                <!--<Property Name=\"Position\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\"\/>-->\n";
    #        }
    #        elsif($line =~ /rotation\s*x=\"(-?[0-9\.]*)\"\s*y=\"(-?[0-9\.]*)\"\s*z=\"(-?[0-9\.]*)\"\s*w=\"(-?[0-9\.]*)\"/i)
    #        {
    #            print "                <!--<Property Name=\"Orientation\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\" Value4=\"$4\"\/>-->\n";
    #        }
    #        elsif($line =~ /scale\s*x=\"(-?[0-9\.]*)\"\s*y=\"(-?[0-9\.]*)\"\s*z=\"(-?[0-9\.]*)\"/i)
    #        {
    #            print "                <!--<Property Name=\"Scale\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\"\/>-->\n";
    #        }
    #        elsif($line =~ /target\s*name=\"(.*)\"/i)
    #        {
    #            #BUGBUG.. implement!
    #        }
    #        else
    #        {
    #            print "                <!-- $line -->\n";
    #        }
    #    }
    #    $i--;
    #    print "            <!--<\/Properties>-->\n";
    #    print "        <!--<\/Object>-->\n";
    #}
    #elsif($line =~ /<\/camera/i)
    #{
    #}
    #elsif($line =~ /<\/cameras/i)
    #{
    #}
    elsif($line =~ /<entity\s*name=\"(.*)\"\s*hidden=\"(.*)\"\s*filename=\"(.*)\"\s*CastShadows=\"(.*)\"\s*ReceiveShadows=\"(.*)\"/i)
    {

        print "        <Object Name=\"$1\">\n";
        $filename = $3;
        $CastShadows = $4;
#        $ReceiveShadows = $5;
        
        print "            <Properties SystemType=\"Geometry\">\n";
        while(!($file[++$i] =~ /<\/entity/i))
        {
            $line = $file[$i];
            chomp($line);

            if($line =~ /position\s*x=\"(-?[0-9\.]*)\"\s*y=\"(-?[0-9\.]*)\"\s*z=\"(-?[0-9\.]*)\"/i)
            {
                print "                <Property Name=\"Position\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\"\/>\n";
            }
            elsif($line =~ /rotation\s*x=\"(-?[0-9\.]*)\"\s*y=\"(-?[0-9\.]*)\"\s*z=\"(-?[0-9\.]*)\"\s*w=\"(-?[0-9\.]*)\"/i)
            {
                print "                <Property Name=\"Orientation\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\" Value4=\"$4\"\/>\n";
            }
            elsif($line =~ /scale\s*x=\"(-?[0-9\.]*)\"\s*y=\"(-?[0-9\.]*)\"\s*z=\"(-?[0-9\.]*)\"/i)
            {
                print "                <Property Name=\"Scale\" Value1=\"$1\" Value2=\"$2\" Value3=\"$3\"\/>\n";
            }
            else
            {
                print "                <!-- $line -->\n";
            }
        }
        $i--;
        print "            <\/Properties>\n";

        print "            <Properties SystemType=\"Graphics\" ObjectType=\"Mesh\">\n";
        $parent_specified = 0;
        if($filename =~ /parent=/i)
        {
            $parent_specified = 1;
        }

        if($parent_specified)
        {
            $filename =~ s/(.*)\"\s*parent=\"(.*)//i;
            $filename = $1;
            $parent = $2;
        }


        $warntext = "Cannot handle Parent property for meshes yet.";
        if(!$no_warn) 
        {
            if($no_rep_warn)
            {
                $warn[$warntext]++;
            }
            if($warn[$warntext] < 2)
            {
                print "                <!-- !!! WARNING !!! $warntext !!! -->\n";
            }
        }


        $ARGV[0] =~ s/\.osm//i;
        print "                <Property Name=\"Mesh\" Value1=\"$filename\"\/>\n";
        $warntext = "Material Property is not part of Geometry. It is a part of the mesh.";
        if(!$no_warn) 
        {
            if($no_rep_warn)
            {
                $warn[$warntext]++;
            }
            if($warn[$warntext] < 2)
            {
                print "                <!-- !!! WARNING !!! $warntext !!! -->\n";
            }
        }

        print "                <Property Name=\"CastShadows\" Value1=\"";
        if($CastShadows eq "yes") { print "1"; } else { print "0"; }
        print "\"\/>\n";
# OGRE doesn't support a RxShadows option for Entities(Movable Objects).
# It supports it only for materials.
#        print "                <Property Name=\"ReceiveShadows\" Value1=\"";
#        if($ReceiveShadows eq "yes") { print "1"; } else { print "0"; }
#        print "\"\/>\n";
        print "            </Properties>\n";
        print "        <\/Object>\n";
    }
    elsif($line =~ /<\/entity/i)
    {
    }
    elsif($line =~ /<\/entities/i)
    {
        print "    <\/Objects>\n\n";

        print "    <Objects>\n";
        print "        <Object Name=\"MainCamera\">\n";
        print "            <Properties SystemType=\"Geometry\">\n";
        print "                <Property Name=\"Position\" Value1=\"0.0\" Value2=\"1000.0\" Value3=\"4000.0\"\/>\n";
        print "                <Property Name=\"Orientation\" Value1=\"-0.124674733\" Value2=\"0.0\" Value3=\"0.0\" Value4=\"0.992197667\"\/>\n";
        print "            <\/Properties>\n";
        print "            <Properties SystemType=\"Graphics\" ObjectType=\"Camera\">\n";
        print "                <Property Name=\"FOVy\" Value1=\"0.523598\"\/>\n";
        print "                <Property Name=\"ClipDistances\" Value1=\"5.0\" Value2=\"60000.0\"\/>\n";
        print "            <\/Properties>\n";
        print "            <Properties SystemType=\"Input\"\/>\n";
        print "        <\/Object>\n";
        print "    <\/Objects>\n\n";
    }
    else
    {
        print "<!-- $line -->\n";
    }

}

