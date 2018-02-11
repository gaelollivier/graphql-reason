// wire-up Reason context with js code

// import reason code, relative to build/
import { createContext } from '../lib/js/src/context';

// just export Reason createContext here for now
// TODO: expose js request to Reason code (for extracting auth info, for example)
export default createContext;
