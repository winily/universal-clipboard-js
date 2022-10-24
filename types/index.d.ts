// alias
export function clear(): void

// buffer
export function readBuffer(format?: string): Buffer
export function writeBuffer(data: Buffer, format?: string): boolean

// text
export function readText(format?: string): string
export function writeText(text: string, format?: string): boolean

// format
export const FORMAT_PLAIN_TEXT: string
export const FORMAT_FILE_URL: string
