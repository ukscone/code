class Klass:
    def __init__(self, name):
        self.name = name
        self.parents = []
        self.attributes = []
        self.operations = []
    
    def add_parent(self, name):
        self.parents.append(name)
    
    def add_attribute(self, _type, name):
        self.attributes.append((name, _type))
            
    def add_operation(self, return_type, name, args):
        self.operations.append((name, args, return_type))
        
    def _name_out(self):
        return self.name
        
    def _attribute_out(self):
        ret = []
        for a in self.attributes:
            astr = a[0] + ' : ' + a[1] + '\\l'
            ret.append(astr)
        return "".join(ret)
        
    def _operation_out(self):
        ret = []
        for o in self.operations:
            ostr = o[0] + '('
            if o[1]:
                for arg in o[1].split(', '):
                    arg = arg.strip()
                    s = arg.split(' ')
                    if len(s) == 2:
                        ostr += s[1] + ' : ' + s[0]
                    else:
                        ostr += s[2] + ' : ' + s[0] + ' ' + s[1]
                    ostr += ', '
                ostr = ostr[:-2]
            ostr += ') : ' + o[2] + '\\l'
            ret.append(ostr)
        return "".join(ret)
        
    def uml_out(self):
        return """\t%(name)s [\n\t\tlabel = "{%(name)s|%(attributes)s|%(operations)s}"\n\t]""" % \
            {'name': self._name_out(), 'attributes': self._attribute_out(), 'operations': self._operation_out()}
        
    def parents_out(self):
        ret = []
        for parent in self.parents:
            parent = parent.strip()
            if parent:
                pstr = '\t' + self.name + ' -> ' + parent + '\n'
                ret.append(pstr)
        return "".join(ret)
