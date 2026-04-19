package main

import (
	"bufio"
	"fmt"
	"net/http"
	"os"
	"regexp"
	"sync"
	"time"
)

type Extractor struct {
	RegexEngine          *regexp.Regexp
	CommunitacionChannel chan<- string
}

func WriteRegex(wg *sync.WaitGroup, file string, channel <-chan string) {
	defer wg.Done()
	f, err := os.Create(file)
	if err != nil {
		fmt.Println("Ocurrió un error al crear o intentar abrir el archivo...")
		return
	}
	defer f.Close()
	for i := range channel {
		f.WriteString(i + "\n")
	}
	f.Sync()
}

func Scrap(wg *sync.WaitGroup, url string, extractors ...Extractor) {
	defer wg.Done()
	client := &http.Client{
		Timeout: 15 * time.Second,
	}
	res, err := client.Get(url)
	if err != nil {
		fmt.Printf("No se pudo accesar a la url: %s \t\n", url)
		return
	}
	defer res.Body.Close()
	reader := bufio.NewScanner(res.Body)
	for reader.Scan() {
		for i := range extractors {
			for _, v := range extractors[i].RegexEngine.FindAllString(reader.Text(), -1) {
				extractors[i].CommunitacionChannel <- v
			}
		}
	}
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Debe proporcionar al menos una url para funcionar")
		os.Exit(-1)
	}

	regexEmail := `([A-Za-z0-9]+[\.+_-]?)*[A-Za-z0-9]+@([A-Za-z0-9]+\.)+[A-Za-z]+`
	regexURL := `https?://([A-Za-z0-9\-]+\.)+[A-Za-z0-9\-]+(/[A-Za-z0-9\-*?+=%&/#\._]*)?`
	regexDate := `\b(((0[1-9]|[1-2][0-9]|3[0-1])/(0[1-9]|1[0-2])/(\d{2}|\d{4}))|((0[1-9]|[1-2][0-9]|3[0-1])-(0[1-9]|1[0-2])-(\d{2}|\d{4}))|((0[1-9]|[1-2][0-9]|3[0-1])\.(0[1-9]|1[0-2])\.(\d{2}|\d{4})))\b`
	compileDate := regexp.MustCompile(regexDate)
	compileEmail := regexp.MustCompile(regexEmail)
	compileURL := regexp.MustCompile(regexURL)
	var wgWritters sync.WaitGroup
	wgWritters.Add(3)
	chDates := make(chan string)
	chEmails := make(chan string)
	chURL := make(chan string)
	go WriteRegex(&wgWritters, "dates.txt", chDates)
	go WriteRegex(&wgWritters, "emails.txt", chEmails)
	go WriteRegex(&wgWritters, "url.txt", chURL)
	extracts := make([]Extractor, 0, 3)
	extracts = append(extracts, Extractor{RegexEngine: compileEmail, CommunitacionChannel: chEmails}, Extractor{RegexEngine: compileURL, CommunitacionChannel: chURL}, Extractor{RegexEngine: compileDate, CommunitacionChannel: chDates})
	go func() {
		var wgScraps sync.WaitGroup
		for i := 1; i < len(os.Args); i++ {
			wgScraps.Add(1)
			go Scrap(&wgScraps, os.Args[i], extracts...)
		}
		wgScraps.Wait()
		for _, e := range extracts {
			close(e.CommunitacionChannel)
		}
	}()
	wgWritters.Wait()
}